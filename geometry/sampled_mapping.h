// -*- c++ -*-

// +------------------------------------------------------------------------+
// | This file is part of AMSTeL - the Adaptive MultiScale Template Library |
// |                                                                        |
// | Copyright (c) 2002-2020                                                |
// | Thorsten Raasch, Manuel Werner, Jens Kappei, Dominik Lellek,           |
// | Philipp Keding, Alexander Sieber, Henning Zickermann,                  |
// | Ulrich Friedrich, Carsten Weber, Simon Wardein                         |
// +------------------------------------------------------------------------+

#ifndef _AMSTeL_SAMPLED_MAPPING_H
#define _AMSTeL_SAMPLED_MAPPING_H

#include <iostream>
#include <cmath>

#include <geometry/grid.h>
#include <utils/array1d.h>
#include <utils/array2d.h>
#include <algebra/infinite_vector.h>

namespace AMSTeL
{
  /*!
    Abstract base class for a mapping from R^n to R,
    represented by finite many samples on a rectangular grid (Matlab style).
    Meaningful values for n are n=1 and n=2 so far (see specializations).
  */
  template <unsigned int DIM, class C=double>
  class SampledMapping
    : public Grid<DIM>
  {
  public:
    /*!
      default constructor, yields empty mapping
    */
    SampledMapping() {}

    /*!
      copy constructor
    */
    SampledMapping(const SampledMapping<DIM>& sm);

    /*!
      constructor from a given grid, yields zero function
    */
    SampledMapping(const Grid<DIM>& grid);

    /*!
      constructor from a given grid and given values
    */
    SampledMapping(const Grid<DIM>& grid, const Array1D<C>& values);

    /*!
      assignment operator
    */
    SampledMapping<DIM,C>& operator = (const SampledMapping<DIM,C>& sm);

    /*!
      pointwise in-place summation *this += s
      of two sampled mappings over the same grid
    */
    void add(const SampledMapping<DIM,C>& s);
    
    /*!
      pointwise in-place summation *this += alpha * s
      of two sampled mappings over the same grid
    */
    void add(const C alpha, const SampledMapping<DIM,C>& s);

    /*!
      pointwise in-place multiplication *this *= alpha
    */
    void mult(const C alpha);


    /*!
      Matlab output of the sampled mapping onto a stream
    */
    void matlab_output(std::ostream& os,
		       bool add_plot_command = false) const;
    };

  //
  //
  // template specializations to one and two space dimensions

  template <class C>
  class SampledMapping<1,C>
    : public Grid<1>
  {
  public:
    /*!
      default constructor, yields empty mapping
    */
    SampledMapping();

    /*!
      copy constructor
    */
    SampledMapping(const SampledMapping<1,C>& sm);

    /*!
      constructor from a given grid, yields zero function
    */
    SampledMapping(const Grid<1>& grid);

    /*!
      constructor from a given grid and given values
    */
    SampledMapping(const Grid<1>& grid, const Array1D<C>& values);

    /*!
      constructor from given values on 2^{-resolution}\mathbb Z, clipped to [a,b]
    */
    SampledMapping(const int a,
		   const int b,
		   const InfiniteVector<C, int>& values,
		   const int resolution);

    /*!
      assignment operator
    */
    SampledMapping<1,C>& operator = (const SampledMapping<1,C>& sm);

    /*!
      pointwise in-place summation *this += s
      of two sampled mappings over the same grid
    */
    void add(const SampledMapping<1,C>& s);
    
    /*!
      pointwise in-place summation *this += alpha * s
      of two sampled mappings over the same grid
    */
    void add(const C alpha, const SampledMapping<1,C>& s);

    /*!
      pointwise in-place multiplication *this *= alpha
    */
    void mult(const C alpha);

    /*!
      reading access to the function values
    */
    inline const Array1D<C>& values() const { return values_; }

    /*!
      Matlab output of the sampled mapping onto a stream
    */
    void matlab_output(std::ostream& os,
		       bool add_plot_command = false) const;

    /*!
      Gnuplot output of the sampled mapping onto a stream
    */
    void gnuplot_output(std::ostream& os) const;

  protected:
    /*!
      internal storage for the function values
    */
    Array1D<C> values_;
  };

  template <class C>
  class SampledMapping<2,C>
    : public Grid<2>
  {
  public:
    /*!
      default constructor, yields empty mapping
    */
    SampledMapping();

    /*!
      copy constructor
    */
    SampledMapping(const SampledMapping<2,C>& sm);

    /*!
      constructor from a given grid, yields zero function
    */
    SampledMapping(const Grid<2>& grid);

    /*!
      constructor from a given grid and given values
      (columns of the matrix correspond to the x grid)
    */
    SampledMapping(const Grid<2>& grid, const Array2D<C>& values);

    /*!
      assignment operator
    */
    SampledMapping<2,C>& operator = (const SampledMapping<2,C>& sm);

    /*!
      pointwise in-place summation *this += s
      of two sampled mappings over the same grid
    */
    void add(const SampledMapping<2,C>& s);
    
    /*!
      pointwise in-place summation *this += alpha * s
      of two sampled mappings over the same grid
    */
    void add(const C alpha, const SampledMapping<2,C>& s);
    
    /*!
     * add a matrix to the values_ of *this
    */
    void add(const Array2D<C>& mat);
    
    /*!
     add alpha*mat to values_
    */
    void add(const C alpha, const Array2D<C>& mat);

    /*!
      pointwise in-place multiplication *this *= alpha
    */
    void mult(const C alpha);

    /*!
      reading access to the function values
    */
    inline const Array2D<C>& values() const { return values_; }

    /*!
      Matlab output of the sampled mapping onto a stream
    */
    void matlab_output(std::ostream& os,
		       bool add_plot_command = false) const;

    /*!
      Matlab output of the sampled mapping onto a stream
    */
    void gnuplot_output(std::ostream& os) const;


    /*!
      Octave-compatible output of the sampled mapping onto a stream
    */
    void octave_output(std::ostream& os) const;

  protected:
    /*!
      internal storage for the function values
    */
    Array2D<C> values_;
  };


  /*!
    Matlab output for a single SampledMapping
  */
  template <unsigned int DIM, class C>
  void matlab_output(std::ostream& os,
		     const SampledMapping<DIM,C>& sm);

  /*!
    Matlab output for an Array1D of SampledMapping's
  */
  template <unsigned int DIM, class C>
  void matlab_output(std::ostream& os,
		     const Array1D<SampledMapping<DIM,C> >& values);

  /*!
    Octave-compatible output for an Array1D of SampledMapping's
  */
  template <unsigned int DIM, class C>
  void octave_output(std::ostream& os,
		     const Array1D<SampledMapping<DIM,C> >& values);

}

#include "geometry/sampled_mapping.cpp"

#endif