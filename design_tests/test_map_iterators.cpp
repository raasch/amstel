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
 algebra functionality (BLAS level 1 and 2, essentially). Using std::map
 as a protected base class leaves open the option to exchange the internal
 implementation of InfiniteVector, e.g., by a hashed map.
 
 Main design goals and problems:
 1) Read and write access should be of O(N) complexity, N being the number of
    nonzero entries. This is ensured by the standard implementation of
    std::map as a red/black tree. We are aware of the fact that read access via
    std::map::operator [] alone may insert new, unwanted entries into the
    infinite vector. Therefore, since we want to use the notation [] (and not
    methods like std::map::at() which have been available only since C++11),
    we will expose read and write access to the protected base class std:: map
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
  class iterator
  : protected std::map<I,C>::iterator
  {
  public:
    typedef typename std::map<I,C>::iterator::iterator_category iterator_category;
    typedef typename std::map<I,C>::iterator::difference_type difference_type;
    typedef typename std::map<I,C>::iterator::value_type value_type;
    typedef typename std::map<I,C>::iterator::pointer pointer;
    typedef typename std::map<I,C>::iterator::reference reference;
    
    iterator(const typename std::map<I,C>::iterator& it)
    : std::map<I,C>::iterator(it)
    {
    }
    
    bool operator == (const iterator& it) const
    {
      return (static_cast<typename std::map<I,C>::iterator>(*this)
              == static_cast<typename std::map<I,C>::iterator>(it));
    }
    
    bool operator != (const iterator& it) const
    {
      return !(*this == it);
    }
    
    iterator& operator ++ ()
    {
      std::map<I,C>::iterator::operator ++ ();
      return *this;
    }
    
    iterator operator ++ (int step)
    {
      const_iterator r(*this);
      std::map<I,C>::iterator::operator ++ (step);
      return r;
    }
    
    iterator& operator -- ()
    {
      std::map<I,C>::iterator::operator -- ();
      return *this;
    }
    
    iterator operator -- (int step)
    {
      iterator r(*this);
      std::map<I,C>::iterator::operator -- (step);
      return r;
    }
    
    I& index() const
    {
      return (std::map<I,C>::iterator::operator * ()).first;
    }
    
    C& operator * () const
    {
      return (std::map<I,C>::iterator::operator * ()).second;
    }
    
    C* operator -> () const
    {
      return &((std::map<I,C>::iterator::operator ->()).second);
    }
  };
  
  class const_iterator
  : protected std::map<I,C>::const_iterator
  {
  public:
    typedef typename std::map<I,C>::const_iterator::iterator_category iterator_category;
    typedef typename std::map<I,C>::const_iterator::difference_type difference_type;
    typedef typename std::map<I,C>::const_iterator::value_type value_type;
    typedef typename std::map<I,C>::const_iterator::pointer pointer;
    typedef typename std::map<I,C>::const_iterator::reference reference;
    
    const_iterator()
    : std::map<I,C>::const_iterator()
    {
    }
    
    const_iterator(const typename std::map<I,C>::const_iterator& it)
    : std::map<I,C>::const_iterator(it)
    {
    }
    
    const_iterator(const iterator& it)
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
    
    const_iterator& operator ++ ()
    {
      std::map<I,C>::const_iterator::operator ++ ();
      return *this;
    }
    
    const_iterator operator ++ (int step)
    {
      const_iterator r(*this);
      std::map<I,C>::const_iterator::operator ++ (step);
      return r;
    }
    
    const_iterator& operator -- ()
    {
      std::map<I,C>::const_iterator::operator -- ();
      return *this;
    }
    
    const_iterator operator -- (int step)
    {
      const_iterator r(*this);
      std::map<I,C>::const_iterator::operator -- (step);
      return r;
    }
    
    const I& index() const
    {
      return (std::map<I,C>::const_iterator::operator * ()).first;
    }
    
    const C& operator * () const
    {
      return (std::map<I,C>::const_iterator::operator * ()).second;
    }
    
    const C* operator -> () const
    {
      return &((std::map<I,C>::const_iterator::operator ->()).second);
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
  
  size_t size() const
  {
    return std::map<I,C>::size();
  };
  
  bool operator == (const InfiniteVector<C,I>& v) const
  {
#if 0
    return (size()==v.size()) && std::equal(begin(), end(), v.begin()); // does not compile a.t.m.
#else
    const_iterator it(begin()), vit(v.begin());
    do
    {
      if (it==end())
        return (vit==v.end());
      if (vit==v.end())
        return false;
    } while (*it++ == *vit++);
    return false;
#endif
  }
};

template<class C, class I>
std::ostream& operator << (std::ostream& os, const InfiniteVector<C,I>& v)
{
  if (v.begin() == v.end())
  {
    os << "0" << std::endl;
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

template <class C, class I=int>
class AnotherInfiniteVector
: public std::map<I,C>
{
public:
  // Note that the class std::map already has an operator ==, which we
  // override here to check whether std::equal works
  bool operator == (const AnotherInfiniteVector<C,I>& v) const
  {
    return (this->size() == v.size()) && std::equal(this->begin(),this->end(),v.begin());
  }
};

template <class C, class I=int>
class YetAnotherInfiniteVector
: protected std::map<I,C>
{
public:
  // Note that the class std::map already has an operator ==, which we
  // override here to check whether std::equal works
  bool operator == (const YetAnotherInfiniteVector<C,I>& v) const
  {
    return (this->size() == v.size()) && std::equal(this->begin(),this->end(),v.begin());
  }
};

int main()
{
  InfiniteVector<double,int> v;
  
  // test default constructor and operator <<
  cout << "- a zero vector v:" << endl
    << v;
  
  // test constructor from std::map
  std::map<int,double> wmap;
  wmap[42]=23.0;
  wmap[123]=23.0;
  InfiniteVector<double,int> w(wmap);
  cout << "- a vector w created via std::map :" << endl
    << w;

  // test operator == on AnotherInfiniteVector
  AnotherInfiniteVector<double,int> a,b;
  a[1]=2.5;
  b[2]=2.5;
  cout << "- are the vectors a and b equal?" << endl;
  if (a==b)
    cout << "  ... yes!" << endl;
  else
    cout << "  ... no!" << endl;

  // test operator == on YetAnotherInfiniteVector
  YetAnotherInfiniteVector<double,int> ay,by;
  cout << "- are the vectors ay and by equal?" << endl;
  if (ay==by)
    cout << "  ... yes!" << endl;
  else
    cout << "  ... no!" << endl;
  
  // test operator ==
  cout << "- are the vectors v and w equal?" << endl;
  if (v==w)
    cout << "  ... yes!" << endl;
  else
    cout << "  ... no!" << endl;
  
  // test std::count algorithm
  const double number=23.0;
  cout << "- w contains "
  << std::count(w.begin(), w.end(), number)
  << " times the number " << number << endl;

  return 0;
}
