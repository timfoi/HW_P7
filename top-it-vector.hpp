#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace topit
{
  template < class T >
  struct Vector;

  template < class T >
  struct VIter
  {
    explicit VIter(Vector< T > &v, size_t pos);
    bool operator==(const VIter< T > &rhs) const noexcept;
    bool operator!=(const VIter< T > &rhs) const noexcept;
    VIter< T > &operator++() noexcept;
    VIter< T > &operator--() noexcept;
    VIter< T > operator+(size_t i) noexcept;
    VIter< T > operator-(size_t i) noexcept;
    T &operator*() const;

  private:
    Vector< T > &v_;
    size_t pos_;
    friend class Vector< T >;
  };

  template < class T >
  struct VCIter
  {
    explicit VCIter(const Vector< T > &v, size_t pos);
    bool operator==(const VCIter< T > &rhs) const noexcept;
    bool operator!=(const VCIter< T > &rhs) const noexcept;
    VCIter< T > &operator++() noexcept;
    VCIter< T > &operator--() noexcept;
    VCIter< T > operator+(size_t i) noexcept;
    VCIter< T > operator-(size_t i) noexcept;
    const T &operator*() const;

  private:
    const Vector< T > &v_;
    size_t pos_;
    friend class Vector< T >;
  };

  template < class T >
  struct Vector
  {

    Vector();
    Vector(const Vector< T > &rhs);
    Vector(Vector< T > &&rhs) noexcept;
    explicit Vector(std::initializer_list< T > il);

    ~Vector();
    Vector< T > &operator=(const Vector< T > &rhs);
    Vector< T > &operator=(Vector< T > &&rhs) noexcept;

    void swap(Vector< T > &rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    void reserve(size_t cap);
    void shrinkToFit();

    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;

    void pushBack(const T &val);
    void popBack();
    void popFront();
    void pushFront(const T &val);
    T &at(size_t id);
    const T &at(size_t id) const;

    VIter< T > begin() noexcept;
    VIter< T > end() noexcept;
    VCIter< T > begin() const noexcept;
    VCIter< T > end() const noexcept;
    VCIter< T > cbegin() const noexcept;
    VCIter< T > cend() const noexcept;

    void insert(size_t i, const T &val);
    void erase(size_t i);
    void insert(size_t i, const Vector< T > &rhs, size_t beg, size_t end);
    void erase(size_t beg, size_t end);

    template < class FwdIterator >
    void insert(VIter< T > pos, FwdIterator beg, FwdIterator end);
    void insert(VIter< T > pos, const T &value);
    void insert(VIter< T > pos, const T &value, size_t count);
    void erase(VIter< T > beg, VIter< T > end);
    void erase(VIter< T > pos);
    void erase(VIter< T > pos, size_t count);

  private:
    T *data_;
    size_t size_;
    size_t capacity_;

    explicit Vector(size_t k);
    void pushBackImpl(const T &);
    void reserve(size_t pos, size_t k);
  };
  template < class T >
  void clear(T *data, size_t to_pos);
}

template < class T >
T &topit::Vector< T >::at(size_t id)
{
  const Vector< T > *cthis = this;
  const T &ret = cthis->at(id);
  return const_cast< T & >(ret);
}

template < class T >
const T &topit::Vector< T >::at(size_t id) const
{
  if (getSize() && id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}

template < class T >
void topit::Vector< T >::shrinkToFit()
{
  Vector< T > cpy(*this);
  swap(cpy);
}

template < class T >
topit::VIter< T >::VIter(Vector< T > &v, size_t pos):
  v_(v),
  pos_(pos)
{}

template < class T >
bool topit::VIter< T >::operator==(const VIter< T > &rhs) const noexcept
{
  return std::addressof(v_) == std::addressof(rhs.v_) && pos_ == rhs.pos_;
}

template < class T >
bool topit::VIter< T >::operator!=(const VIter< T > &rhs) const noexcept
{
  return !(*this == rhs);
}

template < class T >
topit::VIter< T > &topit::VIter< T >::operator++() noexcept
{
  ++pos_;
  return *this;
}

template < class T >
topit::VIter< T > &topit::VIter< T >::operator--() noexcept
{
  --pos_;
  return *this;
}

template < class T >
topit::VIter< T > topit::VIter< T >::operator+(size_t i) noexcept
{
  return VIter< T >(v_, pos_ + i);
}

template < class T >
topit::VIter< T > topit::VIter< T >::operator-(size_t i) noexcept
{
  return VIter< T >(v_, pos_ - i);
}

template < class T >
T &topit::VIter< T >::operator*() const
{
  if (pos_ >= v_.getSize()) {
    throw std::out_of_range("Iterator out of range");
  }
  return v_[pos_];
}

template < class T >
topit::VCIter< T >::VCIter(const Vector< T > &v, size_t pos):
  v_(v),
  pos_(pos)
{}

template < class T >
bool topit::VCIter< T >::operator==(const VCIter< T > &rhs) const noexcept
{
  return std::addressof(v_) == std::addressof(rhs.v_) && pos_ == rhs.pos_;
}

template < class T >
bool topit::VCIter< T >::operator!=(const VCIter< T > &rhs) const noexcept
{
  return !(*this == rhs);
}

template < class T >
topit::VCIter< T > &topit::VCIter< T >::operator++() noexcept
{
  ++pos_;
  return *this;
}

template < class T >
topit::VCIter< T > &topit::VCIter< T >::operator--() noexcept
{
  --pos_;
  return *this;
}

template < class T >
topit::VCIter< T > topit::VCIter< T >::operator+(size_t i) noexcept
{
  return VCIter< T >(v_, pos_ + i);
}

template < class T >
topit::VCIter< T > topit::VCIter< T >::operator-(size_t i) noexcept
{
  return VCIter< T >(v_, pos_ - i);
}

template < class T >
const T &topit::VCIter< T >::operator*() const
{
  if (pos_ >= v_.getSize()) {
    throw std::out_of_range("Iterator out of range");
  }
  return v_[pos_];
}

template < class T >
topit::VIter< T > topit::Vector< T >::begin() noexcept
{
  return VIter< T >(*this, 0);
}

template < class T >
topit::VIter< T > topit::Vector< T >::end() noexcept
{
  return VIter< T >(*this, size_);
}

template < class T >
topit::VCIter< T > topit::Vector< T >::begin() const noexcept
{
  return VCIter< T >(*this, 0);
}

template < class T >
topit::VCIter< T > topit::Vector< T >::end() const noexcept
{
  return VCIter< T >(*this, size_);
}

template < class T >
topit::VCIter< T > topit::Vector< T >::cbegin() const noexcept
{
  return VCIter< T >(*this, 0);
}

template < class T >
topit::VCIter< T > topit::Vector< T >::cend() const noexcept
{
  return VCIter< T >(*this, size_);
}

template < class T >
void topit::Vector< T >::insert(size_t i, const T &val)
{
  if (i > size_) {
    throw std::out_of_range("Index is more than size");
  }
  Vector< T > cpy(size_ + 1);
  try {
    for (; cpy.size_ < i; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_]);
    }
    new (cpy.data_ + cpy.size_++) T(val);
    for (; cpy.size_ < size_ + 1; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_ - 1]);
    }
  } catch (...) {
    clear(cpy.data_, cpy.size_);
    ::operator delete(cpy.data_);
    throw;
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::reserve(size_t cap)
{
  if (capacity_ >= cap) {
    return;
  }
  T *d = static_cast< T * >(::operator new(sizeof(T) * cap));
  size_t i = 0;
  try {
    for (; i < getSize(); ++i) {
      new (d + i) T(std::move(data_[i]));
    }
  } catch (...) {
    for (size_t j = 0; j < i; ++j) {
      (d + j)->~T();
    }
    ::operator delete(d);
    throw;
  }
  for (size_t j = 0; j < size_; ++j) {
    (data_ + j)->~T();
  }
  ::operator delete(data_);
  data_ = d;
  capacity_ = cap;
}

template < class T >
void topit::Vector< T >::erase(size_t i)
{
  if (i >= size_) {
    throw std::out_of_range("Index is more than size");
  }
  Vector< T > cpy(size_ - 1);
  try {
    for (; cpy.size_ < i; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_]);
    }
    for (; cpy.size_ < size_ - 1; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_ + 1]);
    }
  } catch (...) {
    clear(cpy.data_, cpy.size_);
    ::operator delete(cpy.data_);
    throw;
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::pushBackImpl(const T &val)
{
  new (data_ + size_++) T(val);
}

template < class T >
void topit::Vector< T >::insert(size_t i, const Vector< T > &rhs, size_t beg, size_t end)
{
  if (i > size_) {
    throw std::out_of_range("Index more than size");
  }
  if (end > rhs.getSize()) {
    throw std::range_error("End index more than size of rhs");
  }
  if (end < beg) {
    throw std::range_error("End less than begin");
  }
  size_t add = end - beg;
  Vector< T > cpy(size_ + add);
  try {
    for (; cpy.size_ < i; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_]);
    }
    for (; cpy.size_ < i + add; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T(rhs[beg + cpy.size_ - i]);
    }
    for (; cpy.size_ < size_ + add; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_ - add]);
    }
  } catch (...) {
    clear(cpy.data_, cpy.size_);
    ::operator delete(cpy.data_);
    throw;
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::erase(size_t beg, size_t end)
{
  if (!size_) {
    throw std::out_of_range("empty vector");
  }
  if (end > size_) {
    throw std::range_error("end more than size");
  }
  if (beg > end) {
    throw std::range_error("Beg more than end");
  }
  size_t rem = end - beg;
  Vector< T > cpy(size_ - rem);
  try {
    for (; cpy.size_ < beg; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_]);
    }
    for (; cpy.size_ < size_ - rem; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_ + rem]);
    }
  } catch (...) {
    clear(cpy.data_, cpy.size_);
    ::operator delete(cpy.data_);
    throw;
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::insert(VIter< T > pos, const T &value)
{
  insert(pos.pos_, value);
}
template < class T >
void topit::Vector< T >::insert(VIter< T > pos, const T &value, size_t count)
{
  Vector< T > cpy(size_ + count);
  try {
    for (; cpy.size_ < pos.pos_; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this).at(cpy.size_));
    }
    for (size_t i = 0; i < count; ++i) {
      new (cpy.data_ + cpy.size_++) T(value);
    }
    for (; pos != (*this).end(); ++pos) {
      new (cpy.data_ + cpy.size_++) T(*pos);
    }
  } catch (...) {
    clear(cpy.data_, cpy.size_);
    ::operator delete(cpy.data_);
    throw;
  }
  swap(cpy);
}

template < class T >
template < class FwdIterator >
void topit::Vector< T >::insert(VIter< T > pos, FwdIterator beg, FwdIterator end)
{
  size_t count = 0;
  auto cpyBeg = beg;
  while (cpyBeg != end) {
    ++count;
    ++cpyBeg;
  }
  Vector< T > cpy(size_ + count);
  try {
    for (; cpy.size_ < pos.pos_; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this).at(cpy.size_));
    }
    for (; beg != end; ++beg) {
      new (cpy.data_ + cpy.size_++) T(*beg);
    }
    for (; pos != (*this).end(); ++pos) {
      new (cpy.data_ + cpy.size_++) T(*pos);
    }
  } catch (...) {
    clear(cpy.data_, cpy.size_);
    ::operator delete(cpy.data_);
    throw;
  }
  swap(cpy);
}

template < class T >
void topit::clear(T *data, size_t to_pos)
{
  for (size_t j = 0; j < to_pos; ++j) {
    (data + j)->~T();
  }
}

template < class T >
void topit::Vector< T >::erase(VIter< T > pos)
{
  erase(pos.pos_);
}
template < class T >
void topit::Vector< T >::erase(VIter< T > beg, VIter< T > end)
{
  erase(beg.pos_, end.pos_);
}
template < class T >
void topit::Vector< T >::erase(VIter< T > pos, size_t count)
{
  erase(pos.pos_, pos.pos_ + count);
}

template < class T >
topit::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  try {
    for (auto &&v : il) {
      new (data_ + size_++) T(std::move(v));
    }
  } catch (...) {
    for (size_t i = 0; i < size_; ++i) {
      (data_ + i)->~T();
    }
    throw;
  }
}

template < class T >
void topit::Vector< T >::reserve(size_t pos, size_t k)
{
  if (pos > size_) {
    throw std::out_of_range("Pos more than size");
  }
  Vector< T > cpy(size_ + k);
  try {
    for (; cpy.size_ < pos; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_]);
    }
    for (; cpy.size_ < size_; ++cpy.size_) {
      new (cpy.data_ + cpy.size_ + k) T((*this)[cpy.size_]);
    }
  } catch (...) {
    for (size_t i = 0; i < pos; ++i) {
      (cpy.data_ + i)->~T();
    }
    for (size_t i = pos; i < cpy.size_; ++i) {
      (cpy.data_ + i + k)->~T();
    }
    ::operator delete(cpy.data_);
    throw;
  }
  swap(cpy);
}

template < class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template < class T >
topit::Vector< T >::Vector(size_t k):
  data_(static_cast< T * >(::operator new(sizeof(T) * k))),
  size_(0),
  capacity_(k)
{}

template < class T >
topit::Vector< T >::Vector(const Vector< T > &rhs):
  Vector(rhs.getSize())
{
  try {
    for (; size_ < rhs.getSize(); ++size_) {
      new (data_ + size_) T(rhs[size_]);
    }
  } catch (...) {
    for (size_t i = 0; i < size_; ++i) {
      (data_ + i)->~T();
    }
    throw;
  }
}

template < class T >
topit::Vector< T >::Vector(Vector< T > &&rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
  rhs.size_ = 0;
  rhs.capacity_ = 0;
}

template < class T >
topit::Vector< T >::Vector::~Vector()
{
  clear(data_, size_);
}

template < class T >
topit::Vector< T > &topit::Vector< T >::operator=(const Vector< T > &rhs)
{
  if (this == std::addressof(rhs)) {
    return *this;
  }

  Vector< T > copy(rhs);
  swap(copy);
  return *this;
}

template < class T >
topit::Vector< T > &topit::Vector< T >::operator=(Vector< T > &&rhs) noexcept
{
  if (this == std::addressof(rhs)) {
    return *this;
  }

  Vector< T > temp(std::move(rhs));
  swap(temp);
  return *this;
}

template < class T >
void topit::Vector< T >::swap(Vector< T > &rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template < class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return size_ == 0;
}

template < class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template < class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template < class T >
T &topit::Vector< T >::operator[](size_t id) noexcept
{
  assert(id < getSize());
  return data_[id];
}

template < class T >
const T &topit::Vector< T >::operator[](size_t id) const noexcept
{
  assert(id < getSize());
  return data_[id];
}

template < class T >
void topit::Vector< T >::pushBack(const T &val)
{
  if (size_ == capacity_) {
    size_t newCap = (capacity_ == 0 ? 1 : capacity_ * 2);
    reserve(newCap);
  }
  pushBackImpl(val);
}

template < class T >
void topit::Vector< T >::popBack()
{
  assert(size_ > 0);
  (data_ + --size_)->~T();
}

template < class T >
void topit::Vector< T >::popFront()
{
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty");
  }
  erase(0);
}

template < class T >
void topit::Vector< T >::pushFront(const T &val)
{
  Vector< T > cpy(size_ + 1);
  try {
    new (cpy.data_) T(val);
    for (cpy.size_ = 1; cpy.size_ < size_ + 1; ++cpy.size_) {
      new (cpy.data_ + cpy.size_) T((*this)[cpy.size_ - 1]);
    }
  } catch (...) {
    clear(cpy.data_, cpy.size_);
    ::operator delete(cpy.data_);
    throw;
  }
  swap(cpy);
}

#endif