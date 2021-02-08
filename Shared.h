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
    Shared(T* ptr = nullptr):m_shared_ptr(ptr){
      number_ptr = 0;
    }

    /**
     * @brief Destructor
     */
    ~Shared() {
      // Tell other pointers that this one has been delete and check if object need to be free
      number_ptr--;
      if(m_shared_ptr){
        delete m_shared_ptr;
      }
    }

    /**
     * @brief Copy constructor
     */
    Shared(const Shared<T>& other):m_shared_ptr(other.m_shared_ptr) {
      other->number_ptr += 1;
      number_ptr = other.number_ptr;
    }

    /**
     * @brief Move constructor
     */
    Shared(Shared&& other):m_shared_ptr(std::exchange(other.m_shared_ptr, nullptr)){
      number_ptr = other.number_ptr;
    }

    /**
     * @brief Copy assignment
     */
    Shared& operator=(const Shared& other) {
      return *this;
    }

    /**
     * @brief Move assignment
     */
    Shared& operator=(Shared&& other) {
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
      return T();
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
      return number_ptr;
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
    int number_ptr;
  };
}

#endif // SP_SHARED_H