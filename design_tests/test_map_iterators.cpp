#include <iostream>
#include <map>
#include <algorithm>

/*
 As one of the core ingredients of the AMSTeL library, we will use a C++
 implementation of infinite real-valued sequences over a countable index set
 with only finitely many nontrivial entries. Mathematically speaking, a minimal
 implementation provides something like c_0, the space of all finitely
 supported, real-valued sequences over the natural numbers.
 
 In this design test program, we will work out a minimal C++ implementation of
 such objects, which will be called InfiniteVector. In order to use as much
 well-tested code from the standard library as possible, we intend to derive
 the class InfiniteVector from std::map and endow it with some standard linear
 algebra functionality (BLAS level 1 and 2, essentially).
 
 Main design goals and problems:
 1) Read and write access should be of O(N) complexity, N being the number of
    nonzero entries. We are aware of the fact that read access via
    std::map::operator [] alone may insert new, unwanted entries into the
    infinite vector. Therefore, since we want to use the notation [] (and not
    methods like std::map::at() which have been available only since C++11),
    we will use std::map as a protected base class and expose read and write
    access to it via custom access functions like get_coefficient()
    and set_coefficient().
 2) We want the class InfiniteVector to be an STL-compliant associative
    container class, meaning that all algorithms that can be applied to
    std::map itself should also work for InfiniteVector.
    For example, comparison of two instances of InfiniteVector should be
    feasible with std::equal from <algorithm> (which was the main reason to
    write this design test program). This requires the existence of suitable
    forward iterator classes by which one can walk through the nontrivial
    entries.
 
 Thorsten Raasch, November 2018
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
  public:
    typedef typename std::map<I,C>::const_iterator::difference_type difference_type;
    typedef typename std::map<I,C>::const_iterator::value_type value_type;
    typedef typename std::map<I,C>::const_iterator::pointer pointer;
    typedef typename std::map<I,C>::const_iterator::reference reference;
    typedef typename std::map<I,C>::const_iterator::iterator_category iterator_category;

    const_iterator(const typename std::map<I,C>::const_iterator& it)
    : std::map<I,C>::const_iterator(it)
    {
    }

    bool operator == (const const_iterator& it) const
    {
      return (static_cast<typename std::map<I,C>::const_iterator>(*this)
              == static_cast<typename std::map<I,C>::const_iterator>(it));
    }
    
    bool operator != (const const_iterator& it) const
    {
      return !(*this == it);
    }

    const_iterator operator ++ ()
    {
      std::map<I,C>::const_iterator::operator ++ ();
      return *this;
    }
    
    I index() const
    {
      return (std::map<I,C>::const_iterator::operator *()).first;
    }
    
    const C& operator * () const
    {
      return (std::map<I,C>::const_iterator::operator *()).second;
    }
  };
  
  InfiniteVector()
  : std::map<I,C> ()
  {
  }
  
  InfiniteVector(const std::map<I,C>& source)
  : std::map<I,C> (source)
  {
  }
  
  const_iterator begin() const
  {
    return const_iterator(std::map<I,C>::begin());
  }
  
  const_iterator end() const
  {
    return const_iterator(std::map<I,C>::end());
  };
  
  bool operator == (const InfiniteVector<C,I>& v) const
  {
//    return std::equal(begin(), end(), v.begin());
    return false;
  }
};

template<class C, class I>
std::ostream& operator << (std::ostream& os, const InfiniteVector<C,I>& v)
{
  if (v.begin() == v.end())
  {
    os << "0";
  }
  else
  {
    for (typename InfiniteVector<C,I>::const_iterator it(v.begin());
         it != v.end(); ++it)
    {
      os << it.index() << ": " << *it << std::endl;
    }
  }
  
  return os;
}

int main()
{
  InfiniteVector<double,int> v;
  
  cout << "- a zero vector v:" << endl
    << v << endl;
  
  std::map<int,double> wmap;
  wmap[42]=23.0;
  InfiniteVector<double,int> w(wmap);
  cout << "- a vector w created via std::map:" << endl
    << w << endl;

  cout << "- are the vectors v and w equal?" << endl;
  if (v==w)
    cout << "  ... yes!" << endl;
  else
    cout << "  ... no!" << endl;
  
  return 0;
}
