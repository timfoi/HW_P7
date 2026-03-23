#include "top-it-vector.hpp"
#include <iostream>
#include <utility>

bool testDefaultVector()
{
  topit::Vector<int> v;
  return v.isEmpty();
}

bool testVectorWithValue()
{
  topit::Vector<int> v;
  v.pushBack(1);
  return !v.isEmpty();
}

bool testElementAccess()
{
  topit::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  return v[0] == 1 && v[1] == 2;
}

bool testCopyConstructor()
{
  topit::Vector<int> v;
  v.pushBack(1);
  topit::Vector<int> yav = v;
  bool isAllEqual = v.getSize() == yav.getSize();
  for (size_t i = 0; i < v.getSize() && isAllEqual; ++i)
  {
    isAllEqual = isAllEqual && v[i] == yav[i];
  }
  return isAllEqual;
}

bool testPushFront()
{
  topit::Vector<int> v;
  v.pushFront(1);
  v.pushFront(2);
  return v[0] == 2 && v[1] == 1;
}

bool testCapacity()
{
  topit::Vector<int> v;
  v.pushBack(1);
  return v.getCapacity() == 1;
}

bool testSize()
{
  topit::Vector<int> v;
  v.pushBack(1);
  return v.getSize() == 1;
}

int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair<const char *, test_t>;

  pair_t tests[] =
      {
          {"Default vector should be empty", testDefaultVector},
          {"Vector with any value is not empty", testVectorWithValue},
          {"Inbound access elements", testElementAccess},
          {"Copy constructor should copy all elements", testCopyConstructor},
          {"The element should be added to the beginning of vector", testPushFront},
          {"Capacity of vector should be correct", testCapacity},
          {"Vector size should change when elements are added", testSize}};

  const size_t count = sizeof(tests) / sizeof(pair_t);

  std::cout << std::boolalpha;
  bool pass = true;

  for (size_t i = 0; i < count; ++i)
  {
    const bool res = tests[i].second();
    std::cout << res << ": " << tests[i].first << '\n';
    pass = pass && res;
  }

  std::cout << pass << ": RESULT\n";
}