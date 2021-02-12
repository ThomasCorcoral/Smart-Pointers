#ifndef SP_SHARED_H
#define SP_SHARED_H

#include <cstddef>
#include <utility>
#include <map>

namespace sp {

  /**
   * @brief Smart shared pointer class
   */
  template<typename T>
  class Shared {
  public:
    /**
     * @brief Constructor takes a dynamic pointer
     */
    Shared(T* ptr = nullptr):m_shared_ptr(ptr),m_number_ptr((ptr != nullptr) ? new int(1) : nullptr), m_cnt_weak((ptr != nullptr) ? new int(0) : nullptr){}

    /**
     * @brief Destructor
     */
    ~Shared(){
      if(m_shared_ptr){
        (*this->m_number_ptr)--;
        if((*this->m_number_ptr) == 0){
          if((*this->m_cnt_weak) == 0){
            delete m_cnt_weak;
            delete m_number_ptr;
          }
          delete m_shared_ptr;
        }
      }
    }

    /**
     * @brief Copy constructor
     */
    Shared(const Shared<T>& other):m_shared_ptr(other.m_shared_ptr), m_number_ptr(other.m_number_ptr), m_cnt_weak(other.m_cnt_weak){
      if(other.m_shared_ptr != nullptr){
        (*this->m_number_ptr)++;
      }
    }

    /**
     * @brief Move constructor
     */
    Shared(Shared&& other):m_shared_ptr(std::exchange(other.m_shared_ptr, nullptr)), m_number_ptr(std::exchange(other.m_number_ptr, nullptr)), m_cnt_weak(std::exchange(other.m_cnt_weak, nullptr)){}

    /**
     * @brief Copy assignment
     */
    Shared& operator=(const Shared& other){
      m_shared_ptr = other.m_shared_ptr;
      m_number_ptr = other.m_number_ptr;
      m_cnt_weak = other.m_cnt_weak;
      if (other.m_shared_ptr != nullptr){
          (*this->m_number_ptr)++;
      }
      return *this;
    }

    /**
     * @brief Move assignment
     */
    Shared& operator=(Shared&& other){
      std::swap(other.m_shared_ptr, m_shared_ptr);
      std::swap(other.m_number_ptr, m_number_ptr);
      std::swap(other.m_cnt_weak, m_cnt_weak);
      return *this;
    }

    /**
     * @brief Get the raw pointer
     */
    T* get() {
      return m_shared_ptr;
    }

    /**
     * @brief Get a reference on pointed data
     */
    T& operator*() {
      return *this->m_shared_ptr;
    }

    /**
     * @brief Get the raw pointer
     */
    T* operator->() {
      return m_shared_ptr;
    }

    /**
     * @brief Get the reference number on raw data
     */
    std::size_t count() const {
      return *m_number_ptr;
    }

    /**
     * @brief Get the number of Shared pointed on the current pointer
     */
    bool exists() const {
      return m_shared_ptr != nullptr;
    }

    template<typename> friend class Weak;

  private:
    // implementation defined
    T *m_shared_ptr;
    int *m_number_ptr;
    int *m_cnt_weak;
  };
}

#endif // SP_SHARED_H