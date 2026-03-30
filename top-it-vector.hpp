#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cassert>
#include <cstddef>
#include <utility>

namespace topit
{
  template <class T>
  struct VIter
  {
    explicit VIter(Vector<T> &v, size_t pos);
    bool operator==(const VIter<T> &rhs) const noexcept;
    bool operator!=(const VIter<T> &rhs) const noexcept;
    VIter<T> &operator++() noexcept;
    VIter<T> &operator--() noexcept;
    VIter<T> operator+(size_t i) noexcept;
    VIter<T> operator-(size_t i) noexcept;
    T &operator*() const;

  private:
    Vector<T> &v_;
    size_t pos_;
    friend class Vector<T>;
  };

  template <class T>
  struct VCIter
  {
    explicit VCIter(const Vector<T> &v, size_t pos);
    bool operator==(const VCIter<T> &rhs) const noexcept;
    bool operator!=(const VCIter<T> &rhs) const noexcept;
    VCIter<T> &operator++() noexcept;
    VCIter<T> &operator--() noexcept;
    VCIter<T> operator+(size_t i) noexcept;
    VCIter<T> operator-(size_t i) noexcept;
    const T &operator*() const;

  private:
    const Vector<T> &v_;
    size_t pos_;
    friend class Vector<T>;
  };

  template <class T>
  struct Vector
  {
    using iterator = VIter<T>;
    using const_iterator = VCIter<T>;

    Vector();
    Vector(const Vector<T> &rhs);
    Vector(Vector<T> &&rhs) noexcept;
    explicit Vector(std::initializer_list<T> il);

    ~Vector();
    Vector<T> &operator=(const Vector<T> &rhs);
    Vector<T> &operator=(Vector<T> &&rhs) noexcept;

    void swap(Vector<T> &rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;

    void pushBack(const T &val);
    void popBack();
    void pushFront(const T &val);

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

  private:
    T *data_;
    size_t size_;
    size_t capacity_;

    explicit Vector(size_t k);
  };
}

template <class T>
topit::Vector<T>::Vector(std::initializer_list<T> il) : Vector(il.size())
{
  size_t i = 0;
  for (auto &&val : il)
  {
    data_[i++] = val;
  }
}

template <class T>
topit::Vector<T>::Vector() : data_(nullptr),
                             size_(0),
                             capacity_(0)
{
}

template <class T>
topit::Vector<T>::Vector(size_t k) : data_(new T[k]),
                                     size_(k),
                                     capacity_(k)
{
}

template <class T>
topit::Vector<T>::Vector(const Vector<T> &rhs) : Vector(rhs.getSize())
{
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i] = rhs[i];
  }
}

template <class T>
topit::Vector<T>::Vector(Vector<T> &&rhs) noexcept : data_(rhs.data_),
                                                     size_(rhs.size_),
                                                     capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
  rhs.size_ = 0;
  rhs.capacity_ = 0;
}

template <class T>
topit::Vector<T>::~Vector()
{
  delete[] data_;
}

template <class T>
topit::Vector<T> &topit::Vector<T>::operator=(const Vector<T> &rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }

  Vector<T> copy(rhs);
  swap(copy);
  return *this;
}

template <class T>
topit::Vector<T> &topit::Vector<T>::operator=(Vector<T> &&rhs) noexcept
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }

  Vector<T> temp(std::move(rhs));
  swap(temp);
  return *this;
}

template <class T>
void topit::Vector<T>::swap(Vector<T> &rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template <class T>
bool topit::Vector<T>::isEmpty() const noexcept
{
  return size_ == 0;
}

template <class T>
size_t topit::Vector<T>::getSize() const noexcept
{
  return size_;
}

template <class T>
size_t topit::Vector<T>::getCapacity() const noexcept
{
  return capacity_;
}

template <class T>
size_t topit::Vector<T>::getCapacity() const noexcept
{
  return capacity_;
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
void topit::Vector<T>::pushBack(const T &val)
{
  if (size_ == capacity_)
  {
    size_t newCapacity = (capacity_ == 0 ? 1 : capacity_ * 2);
    T *newData = new T[newCapacity];

    try
    {
      for (size_t i = 0; i < size_; ++i)
      {
        newData[i] = data_[i];
      }
    }
    catch (...)
    {
      delete[] newData;
      throw;
    }

    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
  }

  data_[size_] = val;
  ++size_;
}

template <class T>
void topit::Vector<T>::popBack()
{
  assert(size_ > 0);
  --size_;
}

template <class T>
void topit::Vector<T>::pushFront(const T &val)
{
  if (size_ == capacity_)
  {
    size_t newCapacity = (capacity_ == 0 ? 1 : capacity_ * 2);
    T *newData = new T[newCapacity];

    try
    {
      newData[0] = val;
      for (size_t i = 0; i < size_; ++i)
      {
        newData[i + 1] = data_[i];
      }
    }
    catch (...)
    {
      delete[] newData;
      throw;
    }

    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
    ++size_;
    return;
  }

  for (size_t i = size_; i > 0; --i)
  {
    data_[i] = data_[i - 1];
  }

  data_[0] = val;
  ++size_;
}

#endif