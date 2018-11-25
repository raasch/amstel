#include <iostream>
#include <map>

/*
 As one of the core ingredients of the AMSTeL library, we will need a C++ implementation of infinite
 real-valued sequences over a countable index set with only finitely many nontrivial entries.
 Mathematically speaking, a minimal implementation should provide something like c_0, the space of all
 finitely supported, real-valued sequences over the natural numbers.
 
 In this design test program, we will work out a minimal C++ implementation of such objects,
 which will yield a templated class InfiniteVector. In order to use as much well-tested code from
 the standard library as possible, we intend to derive the class InfiniteVector from std::map.
 
 Main problems/design goals:
 1) We are aware of the fact that read access via std::map::operator [] may insert new entries into the
    infinite vector (which we do not want to). Therefore, since we want to use the operator [] (and not
    methods like std::map::at() that are available since C++11), we will use std::map as a
    protected base class and expose read and write access to it via self-written access functions
    like get_coefficient() and set_coefficient().
 2) We want the class InfiniteVector to be an STL-compliant associative container, meaning that all
    algorithms that can be applied to std::map should also work for InfiniteVector.
    For example, comparison of two instances of InfiniteVector should be done with std::equal from
    <algorithm>, which requires the existence of suitable forward iterator classes that can walk
    through the nontrivial entries.
 */

using std::cout;
using std::endl;

template <class C, class I=int>
class InfiniteVector
  : protected std::map<I,C>
{
public:
  class const_iterator
  : protected std::map<I,C>::const_iterator
  {
  };
  
  const_iterator begin() const;
  const_iterator end() const;
};

template<class C, class I>
std::ostream& operator << (std::ostream& os, const InfiniteVector<C,I>& v)
{
  if (v.begin() ==  v.end())
  {
    os << "0";
  }
//  else
//  {
//    for (typename InfiniteVector<C,I>::const_iterator it(v.begin());
//         it != v.end(); ++it)
//    {
//      os << it.index() << ": " << *it << std::endl;
//    }
//  }
  
  return os;
}

int main()
{
  InfiniteVector<double,int> v;
  
//  cout << "an empty infinite vector:" << endl << v << endl;
  
  return 0;
}
