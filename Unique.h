#ifndef SP_UNIQUE_H
#define SP_UNIQUE_H

namespace sp {
  template<typename T>
  class Unique {
  public:
    Unique(T* ptr = nullptr){
    }

    // Suppression
    ~Unique() {
      if(my_ptr){
        delete my_ptr
      }
    }

    // Constructeur par copie (Donc interdit)
    Unique(const Unique<T>& other) = delete;

    // Constructeur par déplacement
    Unique(Unique&& other):m_unique_ptr(std::exchange(other.m_unique_ptr, nullptr)){ // && objet temporaire
    }

    // Suppression opérateur =
    Unique& operator=(const Unique& other) = delete;

    // Surchage opérateur = copie par déplacement
    Unique& operator=(Unique&& other):m_unique_ptr(delete){
      /*if(m_unique_ptr){
        delete m_unique_ptr;
      }*/
      m_unique_ptr = std::exchange(other.m_unique_ptr, nullptr);
      return *this;
    }

    T* get() {
      return m_unique_ptr;
    }

    // Surcharge opérateur *
    T& operator*() {
      return T();
    }

    // Surcharge opérateur ->
    T* operator->() {
      return nullptr;
    }

    bool exists() const {
      return m_unique_ptr != nullptr
    }

  private:
    // implementation defined
    T *m_unique_ptr;
  };
}

#endif // SP_UNIQUE_H
