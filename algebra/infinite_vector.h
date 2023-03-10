// -*- c++ -*-

// +------------------------------------------------------------------------+
// | This file is part of AMSTeL - the Adaptive MultiScale Template Library |
// |                                                                        |
// | Copyright (c) 2002-2023                                                |
// | Thorsten Raasch, Manuel Werner, Jens Kappei, Dominik Lellek,           |
// | Philipp Keding, Alexander Sieber, Henning Zickermann,                  |
// | Ulrich Friedrich, Dorian Vogel, Carsten Weber, Simon Wardein           |
// +------------------------------------------------------------------------+

#ifndef _AMSTEL_INFINITE_VECTOR_H
#define _AMSTEL_INFINITE_VECTOR_H

#include <map>
#include <set>
#include <algorithm>
#include <iterator>

namespace AMSTeL
{
  // forward declaration of InfiniteVector iterator classes
  template <class C, class I, class CONTAINER> class InfiniteVectorConstIterator;
  
  /*!
    A model class InfiniteVector<C,I> for sparse, infinite-dimensional vectors
      x = (x_i)_{i\in I}
    with entries from a (scalar) class C and indices from an ordered class I;
   
    Internally, the vector entries are be stored in a container class given by
    the template parameter CONTAINER. The default value of CONTAINER is std::map<I,C>
    which yields a robust but not the most efficient implementation for large-scale
    simulations. For such use cases, set CONTAINER to std::unordered_map<I,C>
    or even to a more cache-friendly, proprietary container class.

    The class InfiniteVector provides access to the vector entries via a custom,
    STL-compatible iterator class, and adds some linear algebra functionality
    of level-1 and level-2 BLAS type.
  */
  template <class C, class I = int, class CONTAINER = std::map<I,C> >
  class InfiniteVector
    : protected CONTAINER
  {
  public:
    // friend declarations for iterator classes
    friend class InfiniteVectorConstIterator<C,I,CONTAINER>;
    typedef InfiniteVectorConstIterator<C,I,CONTAINER> const_iterator;
    
    // output type for operator * (), used, e.g., by std::count_if()
    typedef typename CONTAINER::value_type value_type;
    
    /*!
     \brief default constructor: yields empty (zero) vector
    */
    InfiniteVector();

    /*!
     \brief copy constructor
    */
    InfiniteVector(const InfiniteVector<C,I,CONTAINER>& v);

    /*!
     \brief const_iterator pointing to the first nontrivial vector entry
    */
    const_iterator begin() const;

    /*!
     \brief const_iterator pointing to one after the last nontrivial vector entry
    */
    const_iterator end() const;

    /*!
     \brief assignment from another vector
    */
    InfiniteVector<C,I,CONTAINER>& operator = (const InfiniteVector<C,I,CONTAINER>& v);

    /*!
     \brief swap components of two vectors
    */
    void swap (InfiniteVector<C,I,CONTAINER>& v);

    /*!
     \brief test emptyness
    */
    inline bool empty() const { return CONTAINER::empty(); }

    /*!
     \brief set infinite vector to zero
    */
    void clear();
    
    /*!
     \brief equality test
    */
    bool operator == (const InfiniteVector<C,I,CONTAINER>& v) const;

    /*!
     \brief non-equality test
    */
    bool operator != (const InfiniteVector<C,I,CONTAINER>& v) const;

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

//    /*!
//      set all values with modulus strictly below a threshold eta to zero
//      (fabs<C> should exist)
//    */
//    void compress(const double eta = 1e-15);
//
//    /*!
//      apply soft thresholding to all values, with threshold mu
//      (fabs<C> should exist)
//    */
//    void shrinkage(const double mu);

    /*!
      \brief add a value to a vector entry
    */
    void add_coefficient(const I& index, const C increment);

    /*!
      \brief in place summation *this += v
    */
    void add(const InfiniteVector<C,I,CONTAINER>& v);

    /*!
      \brief in place summation *this += s*v
    */
    void add(const C s, const InfiniteVector<C,I,CONTAINER>& v);

    /*!
      in place summation *this = s*(*this) + v
      (AXPY level 1 BLAS routine)
    */
    void sadd(const C s, const InfiniteVector<C,I,CONTAINER>& v);

    /*!
      \brief in place scaling *this *= s
    */
    void scale(const C s);
    
    /*!
      \brief in place summation
    */
    InfiniteVector<C,I,CONTAINER>& operator += (const InfiniteVector<C,I,CONTAINER>& v);

    /*!
      \brief in place subtraction *this -= v
    */
    void subtract(const InfiniteVector<C,I,CONTAINER>& v);

    /*!
      \brief in place subtraction
    */
    InfiniteVector<C,I,CONTAINER>& operator -= (const InfiniteVector<C,I,CONTAINER>& v);

    /*!
      \brief in place multiplication with a scalar
    */
    InfiniteVector<C,I,CONTAINER>& operator *= (const C c);
    
    /*!
      \brief in place division by a (nontrivial) scalar
    */
    InfiniteVector<C,I,CONTAINER>& operator /= (const C c);

    /*!
      \brief inner product
    */
    const C operator * (const InfiniteVector<C,I,CONTAINER>& v) const;

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
    void COARSE(const double eps, InfiniteVector<C,I,CONTAINER>& v) const;
    
    /*!
      weighted root mean square norm
        ||x||_{v,w} = (1/n * sum_i |x_i|^2 / (atol+max(|v_i|,|w_i|)*rtol)^2)^{1/2}
      
      (this has to be modeled as a member function, since partial specialization
      of template functions is not allowed in C++)
    */
    const double wrmsqr_norm(const double atol, const double rtol,
			     const InfiniteVector<C,I,CONTAINER>& v, const InfiniteVector<C,I,CONTAINER>& w) const; 
  };
  
  /*!
   \brief STL-compliant const_iterator scanning the nontrivial entries
   */
  template<class C, class I, class CONTAINER>
  class InfiniteVectorConstIterator
  : protected std::map<I,C,CONTAINER>::const_iterator
  {
  public:
    /*!
     \brief make iterator category accessible
     */
    typedef typename CONTAINER::const_iterator::iterator_category iterator_category;
    
    /*!
     \brief make value type accessible
     */
    typedef typename CONTAINER::const_iterator::value_type value_type;
    
    /*!
     \brief make difference type accessible
     */
    typedef typename CONTAINER::const_iterator::difference_type difference_type;
    
    /*!
     \brief make pointer type accessible
     */
    typedef typename CONTAINER::const_iterator::pointer pointer;
    
    /*!
     \brief make reference type accessible
     */
    typedef typename CONTAINER::const_iterator::reference reference;
    
  private:
    const InfiniteVector<C,I,CONTAINER>& _container;

  public:
    /*!
     \brief constructs a const_iterator from a container and a std::map position
     */
    InfiniteVectorConstIterator(const InfiniteVector<C,I,CONTAINER>& container,
                                const typename CONTAINER::const_iterator& position);
    
    /*!
     \brief dereference const_iterator
     */
    const reference operator * () const;
    
    /*!
     \brief dereference const_iterator
     */
    const pointer operator -> () const;
    
    /*!
     \brief index of current iterator
     */
    const I& index() const;
    
    /*!
     \brief value of current iterator
     */
    const C value() const;
    
    /*!
     \brief compare positions of two iterators
     */
    bool operator == (const InfiniteVectorConstIterator<C,I,CONTAINER>& it) const;
    
    /*!
     \brief non-equality test
     */
    bool operator != (const InfiniteVectorConstIterator<C,I,CONTAINER>& it) const;
    
    /*!
     \brief comparison, corresponding to the order relation on I
     */
    bool operator < (const InfiniteVectorConstIterator<C,I,CONTAINER>& it) const;

    /*!
     \brief prefix increment of the const_iterator
     */
    InfiniteVectorConstIterator& operator ++ ();
    
    /*!
     \brief postfix increment of the const_iterator
     */
    InfiniteVectorConstIterator operator ++ (int step);
  };

  // external InfiniteVector functionality
  
  /*!
   sum of two infinite vectors
   (you should avoid using this operator, since it requires one vector
   to be copied. Use += or add() instead!)
   */
  template <class C, class I, class CONTAINER>
  InfiniteVector<C,I,CONTAINER> operator + (const InfiniteVector<C,I,CONTAINER>& v1,
                                            const InfiniteVector<C,I,CONTAINER>& v2)
  {
    InfiniteVector<C,I,CONTAINER> r(v1);
    r += v2;
    return r;
  }
  
  /*!
   difference of two infinite vectors
   (you should avoid using this operator, since it requires one vector
   to be copied. Use -= or sadd() instead!)
   */
  template <class C, class I, class CONTAINER>
  InfiniteVector<C,I,CONTAINER> operator - (const InfiniteVector<C,I,CONTAINER>& v1,
                                            const InfiniteVector<C,I,CONTAINER>& v2)
  {
    InfiniteVector<C,I,CONTAINER> r(v1);
    r -= v2;
    return r;
  }
  
  //! sign
  template <class C, class I, class CONTAINER>
  InfiniteVector<C,I,CONTAINER> operator - (const InfiniteVector<C,I,CONTAINER>& v)
  {
    InfiniteVector<C,I,CONTAINER> r(v);
    r -= C(-1);
    return r;
  }
  
  //! scalar multiplication
  template <class C, class I, class CONTAINER>
  InfiniteVector<C,I,CONTAINER> operator * (const C c, const InfiniteVector<C,I,CONTAINER>& v)
  {
    InfiniteVector<C,I,CONTAINER> r(v);
    r *= c;
    return r;
  }
  
  /*!
   \brief swap the values of two infinite vectors
   */
  template <class C, class I, class CONTAINER>
  void swap(InfiniteVector<C,I,CONTAINER>& v1, InfiniteVector<C,I,CONTAINER>& v2);
  
  /*!
   \brief stream output for infinite vectors
   */
  template<class C, class I, class CONTAINER>
  std::ostream& operator << (std::ostream& os, const InfiniteVector<C,I,CONTAINER>& v);
}

// include implementation of inline functions
#include <algebra/infinite_vector.cpp>

#endif
