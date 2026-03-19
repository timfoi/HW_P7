#include "top-it-vector.hpp"
#include <iostream>
#include <cassert>

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

bool testElemtAccess()
{
  top::it::Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  return v[0] == 1 && v[1] == 2;
}

bool testCopyConstructor()
{
  topit::Vector<int> v;
  v.pushBack(1);
  topit::Vector<int> copy = v;
  bool isAllEqual = v.getSize() == copy.getSize();
  for (size_t i = 0; isAllEqual && i < v.getSize(); ++i)
  {
    isAllEqual = isAllEqual && (v[i] == copy[i]);
  }
  return isAllEqual;
}

int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair<const char *, test_t>;
  pair_t tests[] = {{"Default vector should be empty", testDefaultVector},
                    {"Vector with any value is not empty", testVectorWithValue},
                    {"Element access should work", testElemtAccess},
                    {"Copy constructor should work", testCopyConstructor}};
  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << res << ": ";
    std::cout << tests[i].first << '\n';
    pass = pass && res;
  }
  std::cout << pass;
  std::cout << ": RESULT\n";
}