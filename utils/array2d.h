// -*- c++ -*-

// +------------------------------------------------------------------------+
// | This file is part of AMSTeL - the Adaptive MultiScale Template Library |
// |                                                                        |
// | Copyright (c) 2002-2020                                                |
// | Thorsten Raasch, Manuel Werner, Jens Kappei, Dominik Lellek,           |
// | Philipp Keding, Alexander Sieber, Henning Zickermann,                  |
// | Ulrich Friedrich, Carsten Weber, Simon Wardein                         |
// +------------------------------------------------------------------------+

#ifndef _AMSTEL_ARRAY2D_H
#define _AMSTEL_ARRAY2D_H

#include <iostream>

namespace AMSTeL
{
  /*!
    This class models matrizes of objects from an arbitrary
    (scalar) class C and is merely a wrapper class around a conventional C-style array.
  */
  template <class C>
  class Array2D
  {
  public:
    /*!
      value type (cf. STL containers)
     */
    typedef C value_type;

    /*!
      pointer type (cf. STL containers)
     */
    typedef value_type* pointer;

    /*!
      const pointer type (cf. STL containers)
    */
    typedef const value_type* const_pointer;

    /*!
      iterator type (cf. STL containers)
    */
    typedef value_type* iterator;

    /*!
      const iterator type (cf. STL containers)
    */
    typedef const value_type* const_iterator;

    /*!
      reference type (cf. STL containers)
    */
    typedef value_type& reference;
    
    /*!
      const reference type (cf. STL containers)
    */
    typedef const value_type& const_reference;

    /*!
      type of indexes and size of the array
     */
    typedef size_t size_type;

    /*!
      default constructor, yields an empty array
     */
    Array2D();

    /*!
      copy constructor
    */
    Array2D(const Array2D<C>& a);
    
    /*!
      Construct an array of positive size s.
      Warning: the builtin types (int, double, ...) may _not_
      automatically be set to _zero_, this may depend on the
      compiler and on the compiler options!
    */
    explicit Array2D(const size_type s);

    Array2D(const size_type row,const size_type col);

    /*!
      release allocated memory
    */
    ~Array2D();

    /*!
      size of the array
    */
    const size_type size() const;

    /*!
      Resize the array to the size row x col.
      Warning: the builtin types (int, double, ...) may _not_
      automatically be set to _zero_, this may depend on the
      compiler and on the compiler options!
    */
    void resize(const size_type row,const size_type col);

    /*!
      assignment operator
    */
    Array2D<C>& operator = (const Array2D<C>& a);

    /*!
      read-only access to the (row,col)-th array member
    */
    const C& operator () (const size_type row, const size_type col) const;

    /*!
      read-write access to the (row,col)-th member
    */
    C& operator () (const size_type row, const size_type col);

    /*!
      read-only iterator access to first element (cf. STL containers)
    */
    const_iterator begin() const;

    /*!
      read-write iterator access to first element (cf. STL containers)
    */
    iterator begin();

    /*!
      read-only iterator access to the element behind the last one
      (cf. STL containers)
    */
    const_iterator end() const;

    /*!
      read-only iterator access to the element behind the last one
      (cf. STL containers)
    */
    iterator end();

    /*!
      swap components of two arrays
    */
    void swap (Array2D<C>& a);

    const size_type row_dimension() const;

    /*!
      column dimension
    */
    const size_type column_dimension() const;

    
  protected:
    /*!
      internal storage is just a pointer to a C array
    */
    C* data_;
    
    /*!
      number of columns
    */
    size_type coldim_;
    
    /*!
      number of rows
    */
    size_type rowdim_;

    /*!
      size of the array
    */
    size_type size_;
  };

  /*!
    stream output for arrays
   */
  template <class C>
  std::ostream& operator << (std::ostream& os, const Array2D<C>& A);
}

// include implementation of inline functions
#include "utils/array2d.cpp"

#endif