#ifndef SP_WEAK_H
#define SP_WEAK_H

#include "Shared.h"

namespace sp {

  /**
   * @brief Smart weak pointer
   */
  template<typename T>
  class Weak {
  public:
    /**
     * @brief Default constructor
     */
    Weak():m_ptr(nullptr),m_cnt_shared(nullptr), m_cnt_weak(nullptr){}

    /**
     * @brief Constructor takes a Shared pointer
     */
    Weak(const Shared<T>& shared):m_ptr(shared.m_shared_ptr), m_cnt_shared(shared.m_number_ptr), m_cnt_weak(shared.m_cnt_weak){
      *m_cnt_weak += 1;
    }

    /**
     * @brief Destructeur
     */
    ~Weak(){
      if(m_ptr){
        *m_cnt_weak -= 1; // tell the shared that the weak is delete
        // If no shared and no more weak, the destructor need to delete the weak counter
        if((*this->m_cnt_shared) == 0 && (*this->m_cnt_weak) == 0){ 
          delete m_cnt_weak;
          delete m_cnt_shared;
        }
      }
    }

    /**
     * @brief Copy constructor
     */
    Weak(const Weak& other):m_ptr(other.m_ptr),m_cnt_weak(other.m_cnt_weak), m_cnt_shared(new int(0)){
      *m_cnt_weak += 1;
    }

    /**
     * @brief Move constructor
     */
    Weak(Weak&& other):m_ptr(std::exchange(other.m_ptr, nullptr)), m_cnt_weak(std::exchange(other.m_cnt_weak, nullptr)), m_cnt_shared(std::exchange(other.m_cnt_shared, nullptr)){}

    /**
     * @brief Copy assignment
     */
    Weak& operator=(const Weak& other) {
      m_ptr = other.m_ptr;
      m_cnt_weak = other.m_cnt_weak;
      m_cnt_shared = other.m_cnt_shared;
      if(m_ptr){
        *m_cnt_weak += 1;
      }
      return *this;
    }

    /**
     * @brief Move assignment
     */
    Weak& operator=(Weak&& other) {
      std::swap(other.m_ptr, m_ptr);
      std::swap(other.m_cnt_weak, m_cnt_weak);
      std::swap(other.m_cnt_shared, m_cnt_shared);
      return *this;
    }

    /**
     * @brief Assignment from Shared
     */
    Weak& operator=(Shared<T>& shared) {
      m_ptr = shared.m_shared_ptr;
      m_cnt_weak = shared.m_cnt_weak;
      m_cnt_shared = shared.m_number_ptr;
      if(m_ptr){
        *m_cnt_weak += 1;
      }
      return *this;
    }

    /**
     * @brief Get a Shared pointer from the Weak pointer
     *
     * If the raw pointer still exists, the method
     * initialize a Shared object. Otherwise, the method
     * retrun a non existing Shared pointeur.
     */
    Shared<T> lock() {
      Shared<T> new_shared_ptr(m_ptr);
      delete(new_shared_ptr.m_number_ptr);
      delete(new_shared_ptr.m_cnt_weak);
      new_shared_ptr.m_number_ptr = m_cnt_shared;
      new_shared_ptr.m_cnt_weak = m_cnt_weak;
      *m_cnt_shared +=1;
      return new_shared_ptr;
    }

  private:
    // implementation defined
    T* m_ptr;
    int* m_cnt_shared;
    int* m_cnt_weak;
  };
}

#endif // SP_WEAK_H
