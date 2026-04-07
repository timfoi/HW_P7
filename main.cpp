#include <iostream>
#include <utility>
#include "top-it-vector.hpp"

bool testConstElementAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  const topit::Vector< int > &cv = v;
  return cv[0] == 1 && cv[1] == 2;
}

bool testAtValid()
{
  topit::Vector< int > v;
  v.pushBack(10);
  v.pushBack(20);
  return v.at(0) == 10 && v.at(1) == 20;
}

bool testAtInvalid()
{
  topit::Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testConstAtValid()
{
  topit::Vector< int > v;
  v.pushBack(7);
  const topit::Vector< int > &cv = v;
  return cv.at(0) == 7;
}

bool testConstAtInvalid()
{
  const topit::Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testSwap()
{
  topit::Vector< int > a;
  topit::Vector< int > b;
  a.pushBack(1);
  b.pushBack(2);
  a.swap(b);
  return a[0] == 2 && b[0] == 1;
}

bool testPopBackMany()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.popBack();
  return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testPopFrontOne()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.popFront();
  return v.isEmpty();
}

bool testInsertByIndexBegin()
{
  topit::Vector< int > v;
  v.pushBack(2);
  v.insert(0, 1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testInsertByIndexMiddle()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(3);
  v.insert(1, 2);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertByIndexEnd()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.insert(2, 3);
  return v.getSize() == 3 && v[2] == 3;
}

bool testEraseByIndex()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.erase(1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}

bool testEraseRangeByIndex()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  v.erase(1, 4);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 5;
}

bool testInsertRangeByIndex()
{
  topit::Vector< int > a;
  topit::Vector< int > b;
  a.pushBack(1);
  a.pushBack(4);
  b.pushBack(2);
  b.pushBack(3);
  a.insert(1, b, 0, 2);
  return a.getSize() == 4 && a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4;
}

bool testIteratorTraversal()
{
  topit::Vector< int > v{1, 2, 3};
  int sum = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    sum += *it;
  }
  return sum == 6;
}

bool testConstIteratorTraversal()
{
  const topit::Vector< int > v{1, 2, 3};
  int sum = 0;
  for (auto it = v.cbegin(); it != v.cend(); ++it) {
    sum += *it;
  }
  return sum == 6;
}

bool testIteratorInsertOne()
{
  topit::Vector< int > v{1, 3};
  v.insert(v.begin() + 1, 2);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testIteratorInsertCount()
{
  topit::Vector< int > v{1, 4};
  v.insert(v.begin() + 1, 2, 2);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 2 && v[3] == 4;
}

bool testIteratorInsertRange()
{
  topit::Vector< int > v{1, 4};
  int arr[] = {2, 3};
  v.insert(v.begin() + 1, arr, arr + 2);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4;
}

bool testIteratorEraseOne()
{
  topit::Vector< int > v{1, 2, 3};
  v.erase(v.begin() + 1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}

bool testIteratorEraseRange()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  v.erase(v.begin() + 1, v.begin() + 4);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 5;
}

bool testIteratorEraseCount()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  v.erase(v.begin() + 1, 3);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 5;
}

bool testDefaultVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testVectorWithValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return !v.isEmpty();
}

bool testElementAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return v[0] == 1 && v[1] == 2;
}

bool testCopyConstructor()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;

  bool isAllEqual = v.getSize() == yav.getSize();
  for (size_t i = 0; i < v.getSize() && isAllEqual; ++i) {
    isAllEqual = isAllEqual && (v[i] == yav[i]);
  }
  return isAllEqual;
}

bool testPushFront()
{
  topit::Vector< int > v;
  v.pushFront(1);
  v.pushFront(2);
  return v[0] == 2 && v[1] == 1;
}

bool testCapacity()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return v.getCapacity() == 1;
}

bool testSize()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return v.getSize() == 1;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(10);
  v.popBack();
  return v.isEmpty();
}

bool testPopFront()
{
  topit::Vector< int > v;
  v.pushBack(10);
  v.pushBack(20);
  v.popFront();
  return v.getSize() == 1 && v[0] == 20;
}

bool testInitializerList()
{
  topit::Vector< int > v{1, 2};
  return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testIterator()
{
  topit::Vector< int > v{1, 2, 3};
  int sum = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    sum += *it;
  }
  return sum == 6;
}

bool testInsertIterator()
{
  topit::Vector< int > v{1, 3};
  v.insert(v.begin() + 1, 2);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testEraseIterator()
{
  topit::Vector< int > v{1, 2, 3};
  v.erase(v.begin() + 1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}

int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair< const char *, test_t >;

  pair_t tests[] = {{"Default vector should be empty", testDefaultVector},
                    {"Vector with any value is not empty", testVectorWithValue},
                    {"Inbound access elements", testElementAccess},
                    {"Copy constructor should copy all elements", testCopyConstructor},
                    {"The element should be added to the beginning of vector", testPushFront},
                    {"Capacity of vector should be correct", testCapacity},
                    {"Vector size should change when elements are added", testSize},
                    {"popBack should remove the last element", testPopBack},
                    {"popFront should remove the first element", testPopFront},
                    {"Initializer list should initialize vector with given values", testInitializerList},
                    {"Iterator should traverse vector", testIterator},
                    {"Iterator insert should work", testInsertIterator},
                    {"Iterator erase should work", testEraseIterator},
                    {"Const element access should work", testConstElementAccess},
                    {"at should return valid element", testAtValid},
                    {"at should throw on invalid index", testAtInvalid},
                    {"Const at should return valid element", testConstAtValid},
                    {"Const at should throw on invalid index", testConstAtInvalid},
                    {"swap should exchange vectors", testSwap},
                    {"popBack should remove last element from non-empty vector", testPopBackMany},
                    {"popFront should remove only element", testPopFrontOne},
                    {"insert by index at begin should work", testInsertByIndexBegin},
                    {"insert by index in middle should work", testInsertByIndexMiddle},
                    {"insert by index at end should work", testInsertByIndexEnd},
                    {"erase by index should work", testEraseByIndex},
                    {"erase range by index should work", testEraseRangeByIndex},
                    {"insert range by index should work", testInsertRangeByIndex},
                    {"Iterator traversal should work", testIteratorTraversal},
                    {"Const iterator traversal should work", testConstIteratorTraversal},
                    {"Iterator insert one should work", testIteratorInsertOne},
                    {"Iterator insert count should work", testIteratorInsertCount},
                    {"Iterator insert range should work", testIteratorInsertRange},
                    {"Iterator erase one should work", testIteratorEraseOne},
                    {"Iterator erase range should work", testIteratorEraseRange},
                    {"Iterator erase count should work", testIteratorEraseCount}};

  const size_t count = sizeof(tests) / sizeof(pair_t);

  std::cout << std::boolalpha;
  bool pass = true;

  for (size_t i = 0; i < count; ++i) {
    const bool res = tests[i].second();
    std::cout << res << ": " << tests[i].first << '\n';
    pass = pass && res;
  }

  std::cout << pass << ": RESULT\n";
}