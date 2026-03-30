#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cassert>
#include <cstddef>
#include <utility>

namespace topit
{
  template <class T>
  struct Vector;

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
    void reserve(size_t cap);

    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;

    void pushBack(const T &val);
    void popBack();
    void pushFront(const T &val);

    VIter<T> begin() noexcept;
    VIter<T> end() noexcept;
    VCIter<T> begin() const noexcept;
    VCIter<T> end() const noexcept;
    VCIter<T> cbegin() const noexcept;
    VCIter<T> cend() const noexcept;

    void insert(size_t i, const T &val);
    void erase(size_t i);
    void insert(size_t i, const Vector<T> &rhs, size_t beg, size_t end);
    void erase(size_t beg, size_t end);

  private:
    T *data_;
    size_t size_;
    size_t capacity_;

    explicit Vector(size_t k);
  };
}

template <class T>
topit::VIter<T>::VIter(Vector<T> &v, size_t pos) : v_(v),
                                                   pos_(pos)
{
}

template <class T>
bool topit::VIter<T>::operator==(const VIter<T> &rhs) const noexcept
{
  return std::addressof(v_) == std::addressof(rhs.v_) && pos_ == rhs.pos_;
}

template <class T>
bool topit::VIter<T>::operator!=(const VIter<T> &rhs) const noexcept
{
  return !(*this == rhs);
}

template <class T>
topit::VIter<T> &topit::VIter<T>::operator++() noexcept
{
  ++pos_;
  return *this;
}

template <class T>
topit::VIter<T> &topit::VIter<T>::operator--() noexcept
{
  --pos_;
  return *this;
}

template <class T>
topit::VIter<T> topit::VIter<T>::operator+(size_t i) noexcept
{
  return VIter<T>(v_, pos_ + i);
}

template <class T>
topit::VIter<T> topit::VIter<T>::operator-(size_t i) noexcept
{
  return VIter<T>(v_, pos_ - i);
}

template <class T>
T &topit::VIter<T>::operator*() const
{
  if (pos_ >= v_.getSize())
  {
    throw std::out_of_range("Iterator out of range");
  }
  return v_[pos_];
}

template <class T>
topit::VCIter<T>::VCIter(const Vector<T> &v, size_t pos) : v_(v),
                                                           pos_(pos)
{
}

template <class T>
bool topit::VCIter<T>::operator==(const VCIter<T> &rhs) const noexcept
{
  return std::addressof(v_) == std::addressof(rhs.v_) && pos_ == rhs.pos_;
}

template <class T>
bool topit::VCIter<T>::operator!=(const VCIter<T> &rhs) const noexcept
{
  return !(*this == rhs);
}

template <class T>
topit::VCIter<T> &topit::VCIter<T>::operator++() noexcept
{
  ++pos_;
  return *this;
}

template <class T>
topit::VCIter<T> &topit::VCIter<T>::operator--() noexcept
{
  --pos_;
  return *this;
}

template <class T>
topit::VCIter<T> topit::VCIter<T>::operator+(size_t i) noexcept
{
  return VCIter<T>(v_, pos_ + i);
}

template <class T>
topit::VCIter<T> topit::VCIter<T>::operator-(size_t i) noexcept
{
  return VCIter<T>(v_, pos_ - i);
}

template <class T>
const T &topit::VCIter<T>::operator*() const
{
  if (pos_ >= v_.getSize())
  {
    throw std::out_of_range("Iterator out of range");
  }
  return v_[pos_];
}

template <class T>
topit::VIter<T> topit::Vector<T>::begin() noexcept
{
  return VIter<T>(*this, 0);
}

template <class T>
topit::VIter<T> topit::Vector<T>::end() noexcept
{
  return VIter<T>(*this, size_);
}

template <class T>
topit::VCIter<T> topit::Vector<T>::begin() const noexcept
{
  return VCIter<T>(*this, 0);
}

template <class T>
topit::VCIter<T> topit::Vector<T>::end() const noexcept
{
  return VCIter<T>(*this, size_);
}

template <class T>
topit::VCIter<T> topit::Vector<T>::cbegin() const noexcept
{
  return VCIter<T>(*this, 0);
}

template <class T>
topit::VCIter<T> topit::Vector<T>::cend() const noexcept
{
  return VCIter<T>(*this, size_);
}

template <class T>
void topit::Vector<T>::insert(size_t i, const T &val)
{
  assert(i <= size_);

  size_t newSize = size_ + 1;
  size_t newCapacity = (capacity_ == 0 ? 1 : capacity_);

  while (newCapacity < newSize)
  {
    newCapacity *= 2;
  }

  T *newData = new T[newCapacity];

  try
  {
    for (size_t j = 0; j < i; ++j)
    {
      newData[j] = data_[j];
    }

    newData[i] = val;

    for (size_t j = i; j < size_; ++j)
    {
      newData[j + 1] = data_[j];
    }
  }
  catch (...)
  {
    delete[] newData;
    throw;
  }

  delete[] data_;
  data_ = newData;
  size_ = newSize;
  capacity_ = newCapacity;
}

template <class T>
void topit::Vector<T>::erase(size_t i)
{
  assert(i < size_);

  for (size_t j = i; j + 1 < size_; ++j)
  {
    data_[j] = data_[j + 1];
  }

  --size_;
}

template <class T>
void topit::Vector<T>::insert(size_t i, const Vector<T> &rhs, size_t beg, size_t end)
{
  assert(i <= size_);
  assert(beg <= end);
  assert(end <= rhs.size_);

  size_t count = end - beg;
  if (count == 0)
  {
    return;
  }

  size_t newSize = size_ + count;
  size_t newCapacity = (capacity_ == 0 ? 1 : capacity_);

  while (newCapacity < newSize)
  {
    newCapacity *= 2;
  }

  T *newData = new T[newCapacity];

  try
  {
    for (size_t j = 0; j < i; ++j)
    {
      newData[j] = data_[j];
    }

    for (size_t j = 0; j < count; ++j)
    {
      newData[i + j] = rhs[beg + j];
    }

    for (size_t j = i; j < size_; ++j)
    {
      newData[j + count] = data_[j];
    }
  }
  catch (...)
  {
    delete[] newData;
    throw;
  }

  delete[] data_;
  data_ = newData;
  size_ = newSize;
  capacity_ = newCapacity;
}

template <class T>
void topit::Vector<T>::erase(size_t beg, size_t end)
{
  assert(beg <= end);
  assert(end <= size_);

  size_t count = end - beg;
  if (count == 0)
  {
    return;
  }

  for (size_t j = beg; j + count < size_; ++j)
  {
    data_[j] = data_[j + count];
  }

  size_ -= count;
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
void topit::Vector<T>::reserve(size_t cap)
{
  if (capacity_ >= cap)
  {
    return;
  }
  T *d = static_cast<T *>(operator new[](cap * sizeof(T)));
  size_t i = 0;
  try
  {
    for (size_t i = 0; i < size_; ++i)
    {
      new (d + i) T(std::move(data_[i]));
    }
  }
  catch (...)
  {
    for (size_t j = 0; j < i; ++j)
    {
      (d + j)->~T();
    }
    operator delete[] d;
    throw;
  }
  delete[] data_;
  data_ = d;
  capacity_ = cap;
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