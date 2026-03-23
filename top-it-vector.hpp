#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cassert>
#include <cstddef>
#include <utility>

namespace topit
{
  template <class T>
  struct Vector
  {
    Vector();
    Vector(const Vector<T> &);
    ~Vector();
    Vector<T> &operator=(const Vector<T> &);

    void swap(Vector<T> &rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;

    void pushBack(const T &);
    void popBack();
    void pushFront(const T &);

  private:
    T *data_;
    size_t size_, capacity_;

    explicit Vector(size_t k);
  };
}

template <class T>
size_t topit::Vector<T>::getCapacity() const noexcept
{
  return capacity_;
}

template <class T>
void topit::Vector<T>::pushFront(const T &val)
{
  Vector<T> cpy(size_ + 1);
  cpy[0] = val;
  for (size_t i = 1; i < cpy.getSize(); ++i)
  {
    cpy[i] = (*this)[i - 1];
  }
  swap(cpy);
}

template <class T>
void topit::Vector<T>::swap(Vector<T> &rhs) noexcept
{
  std::swap(rhs.data_, data_);
  std::swap(rhs.size_, size_);
  std::swap(rhs.capacity_, capacity_);
}

template <class T>
T &topit::Vector<T>::operator[](size_t id) noexcept
{
  assert(id < getSize());
  return data_[id];
}

template <class T>
const T &topit::Vector<T>::operator[](size_t id) const noexcept
{
  assert(id < getSize());
  return data_[id];
}

template <class T>
size_t topit::Vector<T>::getSize() const noexcept
{
  return size_;
}

template <class T>
topit::Vector<T>::Vector(size_t k) : data_(new T[k]), size_(k), capacity_(k)
{
}

template <class T>
topit::Vector<T> &topit::Vector<T>::operator=(const Vector<T> &rhs)
{
  Vector<T> cpy(rhs);
  swap(cpy);
  return *this;
}

template <class T>
topit::Vector<T>::Vector(const Vector<T> &rhs) : Vector(rhs.getSize())
{
  for (size_t i = 0; i < getSize(); ++i)
  {
    data_[i] = rhs[i];
  }
}

template <class T>
bool topit::Vector<T>::isEmpty() const noexcept
{
  return !size_;
}

template <class T>
topit::Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0)
{
}

template <class T>
topit::Vector<T>::~Vector()
{
  delete[] data_;
}

template <class T>
void topit::Vector<T>::pushBack(const T &val)
{
  Vector<T> cpy(size_ + 1);
  cpy[size_] = val;
  for (size_t i = 0; i < size_; ++i)
  {
    cpy[i] = (*this)[i];
  }
  swap(cpy);
}

#endif