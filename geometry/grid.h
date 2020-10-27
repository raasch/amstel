// -*- c++ -*-

// +------------------------------------------------------------------------+
// | This file is part of AMSTeL - the Adaptive MultiScale Template Library |
// |                                                                        |
// | Copyright (c) 2002-2020                                                |
// | Thorsten Raasch, Manuel Werner, Jens Kappei, Dominik Lellek,           |
// | Philipp Keding, Alexander Sieber, Henning Zickermann,                  |
// | Ulrich Friedrich, Carsten Weber, Simon Wardein                         |
// +------------------------------------------------------------------------+

#ifndef _AMSTeL_GRID_H
#define _AMSTeL_GRID_H

#include <utils/array1d.h>

namespace AMSTeL
{
  /*!
    Base class for n-dimensional rectangular grids in the
    style of Matlab. There, rectangular grids are the core ingredients for plotting
    functions from n-D to m-D.
    A 1-dimensional grid is just a vector x holding the mesh points.
    A 2-dimensional grid will be added later
   */
  template <unsigned int DIM>
  class Grid
  {
  public:
    /*!
      default constructor: empty grid
    */
    Grid() {}

    /*!
      number of grid points
    */
    unsigned int size() const;

    /*!
      Matlab output of the grid onto a stream
    */
    void matlab_output(std::ostream& os) const;
  };

  /*!
    specialization of Grid to one space dimension:
    1-dimensional grids are just vectors holding the mesh points.
  */
  template <>
  class Grid<1>
  {
  public:
    /*!
      default constructor: empty grid
    */
    Grid();

    /*!
      construct a 1D grid from an array of 1D points
    */
    Grid(const Array1D<double>& grid);

    /*!
      construct an equidistant 1D grid with N+1 points
    */
    Grid(const double a, const double b, const unsigned int N);

    /*!
      number of grid points
    */
    inline unsigned int size() const { return grid_.size(); }

    /*!
      reading access to the grid points
    */
    inline const Array1D<double>& points() const { return grid_; }

    /*!
      Matlab output of the grid onto a stream
    */
    void matlab_output(std::ostream& os) const;
    
  protected:
    /*!
      internal storage for the grid points
    */
    Array1D<double> grid_;
  };

  
  /*
  grid<2> will be added later
  */
}

#include <geometry/grid.cpp>

#endif