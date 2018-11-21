// -*- c++ -*-

// +------------------------------------------------------------------------+
// | This file is part of AMSTeL - the Adaptive MultiScale Template Library |
// |																		|
// | Copyright (c) 2002-2018												|
// | Thorsten Raasch, Manuel Werner, Jens Kappei, Dominik Lellek,			|
// | Philipp Keding, Alexander Sieber, Henning Zickermann,					|
// | Ulrich Friedrich, Carsten Weber										|
// +------------------------------------------------------------------------+

#ifndef _AMSTEL_INFINITE_VECTOR_H
#define _AMSTEL_INFINITE_VECTOR_H

#include <set>
#include <map>
#include <algorithm>
#include <iterator>

namespace AMSTeL
{
  /*!
    A model class InfiniteVector<C,I> for inherently sparse,
    arbitrarily indexed vectors
      x = (x_i)_{i\in I}
    with entries from a (scalar) class C.
    InfiniteVector<C,I> may act as a realization of coefficient_type in the WaveletTL.
    
    Although internally, we will model InfiniteVector as a map<I,C>,
    the access to the vector entries takes place by a nested iterator
    class (compare the deal.II matrix classes) which is STL-compatible.
  */
  template <class C, class I = int>
  class InfiniteVector
    : protected std::map<I,C>
  {
  public:
    /*!
      \brief default constructor: yields empty (zero) vector
    */
    InfiniteVector();

    /*!
      \brief copy constructor
    */
    InfiniteVector(const InfiniteVector<C,I>& v);

    /*!
      \brief STL-compliant const_iterator scanning the nontrivial entries
    */
    class const_iterator
      : protected std::map<I,C>::const_iterator
    {
    public:
      /*!
	\brief make iterator category accessible
      */
      typedef typename std::map<I,C>::const_iterator::iterator_category iterator_category;

      /*!
	\brief make value type accessible
      */
      typedef typename std::map<I,C>::const_iterator::value_type value_type;

      /*!
	\brief make difference type accessible
      */
      typedef typename std::map<I,C>::const_iterator::difference_type difference_type;

      /*!
	\brief make pointer type accessible
      */
      typedef typename std::map<I,C>::const_iterator::pointer pointer;

      /*!
	\brief make reference type accessible
      */
      typedef typename std::map<I,C>::const_iterator::reference reference;

      /*!
	\brief constructs a const_iterator from a map::const_iterator
      */
      const_iterator(const typename std::map<I,C>::const_iterator& entry);

      /*!
	\brief prefix increment of the const_iterator
      */
      const_iterator& operator ++ ();

      /*!
	\brief postfix increment of the const_iterator
      */
      const_iterator operator ++ (int step);

      /*!
	\brief dereference const_iterator
      */
      const C& operator * () const;

      /*!
	\brief dereference const_iterator
      */
      const C* operator -> () const;

      /*!
	index of current iterator
	(maybe the only difference to an STL iterator)
      */
      I index() const;

      /*!
	\brief compare positions of two iterators
      */
      bool operator == (const const_iterator& it) const;

      /*!
	\brief non-equality test
      */
      bool operator != (const const_iterator& it) const;

      /*!
	\brief comparison, corresponding to the order relation on I
       */
      bool operator < (const const_iterator& it) const;
    };

    /*!
      \brief const_iterator pointing to the first nontrivial vector entry
    */
    const_iterator begin() const;

    /*!
      \brief const_iterator pointing to one after the last nontrivial vector entry
    */
    const_iterator end() const;

    /*!
      STL-compliant const_reverse_iterator scanning the nontrivial entries
      in a reverse way
    */
    class const_reverse_iterator
      : protected std::reverse_iterator<typename std::map<I,C>::const_iterator>
    {
    public:
      /*!
	\brief constructs a const_reverse_iterator from a map::const_iterator
      */
      const_reverse_iterator(const std::reverse_iterator<typename std::map<I,C>::const_iterator>& entry);

      /*!
	\brief prefix increment of the const_reverse_iterator
      */
      const_reverse_iterator& operator ++ ();

      /*!
	\brief postfix increment of the const_reverse_iterator
      */
      const_reverse_iterator operator ++ (int step);

      /*!
	\brief dereference const_reverse_iterator
      */
      const C& operator * () const;

      /*!
	\brief dereference const_reverse_iterator
      */
      const C* operator -> () const;

      /*!
	index of current iterator
	(maybe the only difference to an STL iterator)
      */
      I index() const;

      /*!
	\brief compare positions of two iterators
      */
      bool operator == (const const_reverse_iterator& it) const;

      /*!
	\brief non-equality test
      */
      bool operator != (const const_reverse_iterator& it) const;

      /*!
	\brief comparison, corresponding to the order relation on I
       */
      bool operator < (const const_reverse_iterator& it) const;
    };

    /*!
      \brief const_reverse_iterator pointing to the last nontrivial vector entry
    */
    const_reverse_iterator rbegin() const;

    /*!
      \brief const_reverse_iterator pointing to one before the first last nontrivial vector entry
    */
    const_reverse_iterator rend() const;

    /*!
      \brief assignment from another vector
    */
    InfiniteVector<C,I>& operator = (const InfiniteVector<C,I>& v);

    /*!
      \brief swap components of two vectors
    */
    void swap (InfiniteVector<C,I>& v);

    /*!
      \brief test emptyness
    */
    inline bool empty() const { return std::map<I,C>::empty(); }

    /*!
      \brief set infinite vector to zero
    */
    void clear();
    
    /*!
      \brief equality test
    */
    bool operator == (const InfiniteVector<C,I>& v) const;

    /*!
      \brief non-equality test
    */
    bool operator != (const InfiniteVector<C,I>& v) const;

    /*!
      \brief read-only access to the vector entries
    */
    C operator [] (const I& index) const;

    /*!
      \brief read-only access to the vector entries
    */
    C get_coefficient(const I& index) const;

    /*!
      \brief read-write access to the vector entries
    */
    C& operator [] (const I& index);

    /*!
      \brief set a vector entry
    */
    void set_coefficient(const I& index, const C value);

    /*!
      \brief number of nonzero entries
    */
    size_t size() const;

    /*!
      \brief return support of the current vector as a set
    */
    void support(std::set<I>& supp) const;
    
    /*!
      \brief clip the infinite vector to a given support set
    */
    void clip(const std::set<I>& supp);

    /*!
      set all values with modulus strictly below a threshold to zero
      (fabs<C> should exist)
    */
    void compress(const double eta = 1e-15);
    
    void shrinkage(const double mu);

    /*!
      \brief add a value to a vector entry
    */
    void add_coefficient(const I& index, const C increment);

    /*!
      \brief in place summation *this += v
    */
    void add(const InfiniteVector<C,I>& v);

    /*!
      \brief in place summation *this += s*v
    */
    void add(const C s, const InfiniteVector<C,I>& v);

    /*!
      in place summation *this = s*(*this) + v
      (AXPY level 1 BLAS routine)
    */
    void sadd(const C s, const InfiniteVector<C,I>& v);

    /*!
      \brief in place scaling *this *= s
    */
    void scale(const C s);
    
    /*!
      \brief in place summation
    */
    InfiniteVector<C,I>& operator += (const InfiniteVector<C,I>& v);

    /*!
      \brief in place subtraction *this -= v
    */
    void subtract(const InfiniteVector<C,I>& v);

    /*!
      \brief in place subtraction
    */
    InfiniteVector<C,I>& operator -= (const InfiniteVector<C,I>& v);

    /*!
      \brief in place multiplication with a scalar
    */
    InfiniteVector<C,I>& operator *= (const C c);
    
    /*!
      \brief in place division by a (nontrivial) scalar
    */
    InfiniteVector<C,I>& operator /= (const C c);

    /*!
      \brief inner product
    */
    const C operator * (const InfiniteVector<C,I>& v) const;

    /*!
      helper struct to handle decreasing order in modulus
      for pairs, with respect to the first argument
    */
    struct decreasing_order
      : public std::binary_function<const std::pair<I,C>&,
				    const std::pair<I,C>&,
				    bool>
    {
      inline bool operator () (const std::pair<I,C>& p1,
			       const std::pair<I,C>& p2)
      {
	return (fabs(p1.second) > fabs(p2.second));
      }
    };

    /*!
      \brief weak l_tau norm
    */
    double weak_norm(const double tau) const;

    /*!
      Computes optimal v such that \|*this-v\|_{\ell_2}\le\epsilon;
      "optimal" means taking the largest entries in modulus of *this.
      The vector v does not have to be initialized, it will be cleared
      at the beginning of the algorithm
    */
    void COARSE(const double eps, InfiniteVector<C,I>& v) const;
    
//     /*!
//       Computes v such that \|*this-v\|_{\ell_2}\le\epsilon;
//       In contrast to the usual coarse routine, here the 
//       This routine is a suggestion from Rob Stevenson.
//     */
//     void COARSE(const double eps, InfiniteVector<C,I>& v) const;

    /*!
      weighted root mean square norm
        ||x||_{v,w} = (1/n * sum_i |x_i|^2 / (atol+max(|v_i|,|w_i|)*rtol)^2)^{1/2}
      
      (this has to be modeled as a member function, since partial specialization
      of template functions is not allowed in C++)
    */
    const double wrmsqr_norm(const double atol, const double rtol,
			     const InfiniteVector<C,I>& v, const InfiniteVector<C,I>& w) const; 
  };
  
  /*!
    sum of two infinite vectors
    (you should avoid using this operator, since it requires one vector
    to be copied. Use += or add() instead!)
   */
  template <class C, class I>
  InfiniteVector<C,I> operator + (const InfiniteVector<C,I>& v1,
				  const InfiniteVector<C,I>& v2)
  {
    InfiniteVector<C,I> r(v1);
    r += v2;
    return r;
  }

  /*!
    difference of two infinite vectors
    (you should avoid using this operator, since it requires one vector
    to be copied. Use -= or sadd() instead!)
   */
  template <class C, class I>
  InfiniteVector<C,I> operator - (const InfiniteVector<C,I>& v1,
				  const InfiniteVector<C,I>& v2)
  {
    InfiniteVector<C,I> r(v1);
    r -= v2;
    return r;
  }

  //! sign
  template <class C, class I>
  InfiniteVector<C,I> operator - (const InfiniteVector<C,I>& v)
  {
    InfiniteVector<C,I> r(v);
    r -= C(-1);
    return r;
  }

  //! scalar multiplication
  template <class C, class I>
  InfiniteVector<C,I> operator * (const C c, const InfiniteVector<C,I>& v)
  {
     InfiniteVector<C,I> r(v);
     r *= c;
     return r;
  }

  /*!
    \brief swap the values of two infinite vectors
  */
  template <class C, class I>
  void swap(InfiniteVector<C,I>& v1, InfiniteVector<C,I>& v2);

  /*!
    \brief stream output for infinite vectors
  */
  template<class C, class I>
  std::ostream& operator << (std::ostream& os, const InfiniteVector<C,I>& v);
}

// include implementation of inline functions
#include <algebra/infinite_vector.cpp>

#endif
