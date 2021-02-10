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
    Weak() {
    }

    /**
     * @brief Constructor takes a Shared pointer
     */
    Weak(const Sham_shared_ptrred<T>& shared) {
    }

    /**
     * @brief Destructeur
     */
    ~Weak() {
    }

    /**
     * @brief Copy constructor
     */
    Weak(const Weak& other):m_weak_ptr(other.m_shared_ptr), m_count_ptr(other.m_count_ptr), m_count_objects(other.m_count_objects){
      if(other.m_shared_ptr != nullptr){
        (*this->m_count_ptr)++;
      }
    }

    /**
     * @brief Move constructor
     */
    Weak(Weak&& other):m_adress_object(std::exchange(other.m_adress_object, nullptr)), m_count_ptr(std::exchange(other.m_count_ptr, nullptr)), m_count_objects(std::exchange(other.m_count_objects, nullptr)) {}

    /**
     * @brief Copy assignment
     */
    Weak& operator=(const Weak& other) {
      m_adress_object = other.m_adress_object;
      m_count_ptr = other.m_count_ptr;
      m_count_objects = other.m_count_objects;
      if (nullptr != other.m_adress_object){
        (*this->m_count_ptr)++;
      }
      return *this;
    }

    /**
     * @brief Move assignment
     */
    Weak& operator=(Weak&& other) {
      std::swap(other.m_adress_object, m_adress_object);
      std::swap(other.m_count_ptr, m_count_ptr);
      std::swap(other.m_count_objects, m_count_objects);
      return *this;
    }

    /**
     * @brief Assignment from Shared
     */
    Weak& operator=(Shared<T>& shared) {
      m_adress_object = shared.m_shared_ptr;
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
      if(m_adress_object != nullptr){
        return Shared<T>(m_adress_object);
      }
      return Shared<T>();
    }

  private:
    // implementation defined
    int * m_count_ptr;
    int * m_count_objects;
    T *m_adress_object;
  };
}

#endif // SP_WEAK_H