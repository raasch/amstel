// -*- c++ -*-

// +------------------------------------------------------------------------+
// | This file is part of AMSTeL - the Adaptive MultiScale Template Library |
// |                                                                        |
// | Copyright (c) 2002-2023                                                |
// | Thorsten Raasch, Manuel Werner, Jens Kappei, Dominik Lellek,           |
// | Philipp Keding, Alexander Sieber, Henning Zickermann,                  |
// | Ulrich Friedrich, Dorian Vogel, Carsten Weber, Simon Wardein           |
// +------------------------------------------------------------------------+

#ifndef _AMSTEL_MATRIX_IO_H
#define _AMSTEL_MATRIX_IO_H

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

namespace AMSTeL
{
  /*
    generic input/output routines for MATRIX classes with a standard signature:
    - row_dimension() and column_dimension() determine the size of the matrix
    - operator () yields read access to the matrix entries
  */
  
  /*!
    generic Matlab-style matrix stream output of the form
      [x_{1,1} x_{1,2} ... x_{1,n}; x_{2,1} ... x_{m,n}];
  */
  template <class MATRIX>
  void print_matrix(const MATRIX& M, std::ostream& os)
  {
    os << "[";
    unsigned int precision=15, tabwidth=10;
    unsigned int old_precision = os.precision(precision);
    for (unsigned int row(0); row < M.row_dimension(); row++)
      {
      for (unsigned int column(0); column < M.column_dimension(); column++)
	      {
          os << std::setw(tabwidth) << std::setprecision(precision)
	           << M(row, column);
          if (column < M.column_dimension()-1)
            os << " ";
        }
      if (row < M.row_dimension()-1)
        os << "; ";
      }
    os << "];" << std::endl;
    os.precision(old_precision);
  }
}

#endif
