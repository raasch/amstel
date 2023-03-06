// -*- c++ -*-

// +------------------------------------------------------------------------+
// | This file is part of AMSTeL - the Adaptive MultiScale Template Library |
// |                                                                        |
// | Copyright (c) 2002-2023                                                |
// | Thorsten Raasch, Manuel Werner, Jens Kappei, Dominik Lellek,           |
// | Philipp Keding, Alexander Sieber, Henning Zickermann,                  |
// | Ulrich Friedrich, Dorian Vogel, Carsten Weber, Simon Wardein           |
// +------------------------------------------------------------------------+

#ifndef _AMSTeL_GRID_H
#define _AMSTeL_GRID_H

#include <utils/array1d.h>
#include <utils/array2d.h>

namespace AMSTeL
{
  /*!
    Base class for n-dimensional rectangular grids in the
    style of Matlab. There, rectangular grids are the core ingredients for plotting
    functions from n-D to m-D.
    A 1-dimensional grid is just a vector x holding the mesh points.
    A 2-dimensional grid (a so-called quad-mesh) consists of 2 matrices x and y,
    holding the x- and y-coordinates of the mesh points.
    
    reference: Matlab/Octave help for the command 'surf'
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
    1-dimensional grids are just vectors (1D arrays) holding the mesh points.
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

/*!
    specialization of Grid to two space dimensions:
    2-dimensional grids (quad-meshes) consist of 2 matrices (2D arrays) x and y,
    holding the x- and y-coordinates of the mesh points
  */
  template <>
  class Grid<2>
  {
  public:
    /*!
      default constructor: empty grid
    */
    Grid();

    /*!
      construct a 2D grid from two matrices 
    */
    Grid(const Array2D<double>& gridx, const Array2D<double>& gridy);

    /*!
      construct a 2D tensor product grid from two 1D Grids
    */
    Grid(const Grid<1>& gridx, const Grid<1>& gridy);

    /*!
      construct an equidistant 2D grid with (N_x+1)*(N_y+1) points
    */
    Grid(const double& a_1,const double& a_2, const double& b_1, const double&b_2,
	 const unsigned N_x, const unsigned N_y);

    /*!
      construct an equidistant 2D grid with (N+1)*(N+1) points
    */
    Grid(const double& a_1,const double& a_2, const double& b_1, const double&b_2,
	 const unsigned int N);

    /*!
      number of grid points
    */
    inline unsigned int size() const { return gridx_.size(); }

    /*!
      assignment operator
    */
    Grid<2>& operator = (const Grid<2>& grid);

    /*!
      Matlab output of the grid onto a stream
    */
    void matlab_output(std::ostream& os) const;
    
    /*!
      read access to the grid points
    */
    inline const Array2D<double>& gridx() const { return gridx_; }
    inline const Array2D<double>& gridy() const { return gridy_; }
    
  protected:
    /*!
      internal storage for the grid points
    */
    Array2D<double> gridx_, gridy_;
  };
}

#include <geometry/grid.cpp>

#endif