// implementation for grid.h

namespace AMSTeL
{
  inline
  Grid<1>::Grid()
    : grid_()
  {
  }

  inline
  Grid<1>::Grid(const Array1D<double>& grid)
    : grid_(grid)
  {
  }

  inline
  Grid<1>::Grid(const double a, const double b, const unsigned int N)
    : grid_(N+1)
  {
    for (unsigned int n(0); n <= N; n++)
      grid_[n] = a+((b-a)*n)/N;
  }
  
  inline
  void
  Grid<1>::matlab_output(std::ostream& os) const
  {
    os << "x = "
       << grid_
       << ";"
       << std::endl;
  }
  
  inline
  Grid<2>::Grid()
    : gridx_(), gridy_()
  {
  }

  inline
  Grid<2>::Grid(const Array2D<double>& gridx, const Array2D<double>& gridy)
    : gridx_(gridx), gridy_(gridy)
  {
  }

  inline
  Grid<2>::Grid(const Grid<1>& gridx, const Grid<1>& gridy)
    : gridx_(gridy.size(), gridx.size()),
      gridy_(gridy.size(), gridx.size())
  {
    for (unsigned int n_x(0); n_x < gridx.size(); n_x++)
      for (unsigned int n_y(0); n_y < gridy.size(); n_y++)
	{
	  gridx_(n_y, n_x) = gridx.points()[n_x];
	  gridy_(n_y, n_x) = gridy.points()[n_y];
	}
  }
  
  inline
  Grid<2>::Grid(const double& a_1,const double& a_2, const double& b_1, const double&b_2,
		const unsigned int N_x, const unsigned int N_y)
    : gridx_(N_y+1, N_x+1), gridy_(N_y+1, N_x+1)
  {
    for (unsigned int n_x(0); n_x <= N_x; n_x++)
      for (unsigned int n_y(0); n_y <= N_y; n_y++)
	{
	  gridx_(n_y, n_x) = a_1 + (b_1-a_1)*n_x/N_x;
	  gridy_(n_y, n_x) = a_2 + (b_2-a_2)*n_y/N_y;
	}
  }

  inline
  Grid<2>::Grid(const double& a_1,const double& a_2, const double& b_1, const double&b_2,
		const unsigned int N)
    : gridx_(N+1, N+1), gridy_(N+1, N+1)
  {
    for (unsigned int n_x(0); n_x <= N; n_x++)
      for (unsigned int n_y(0); n_y <= N; n_y++)
	{
	  gridx_(n_y, n_x) = a_1 + (b_1-a_1)*n_x/N;
	  gridy_(n_y, n_x) = a_2 + (b_2-a_2)*n_y/N;
	}
  }
  
  inline
  Grid<2>&
  Grid<2>::operator = (const Grid<2>& grid)
  {
    gridx_ = grid.gridx_;
    gridy_ = grid.gridy_;
    return *this;
  }

  inline
  void
  Grid<2>::matlab_output(std::ostream& os) const
  {
    os << "x = "<< gridx_;
    os << ";" << std::endl;
    
    os << "y = "<< gridy_;
    os << ";" << std::endl;
  }
  
  inline
  void
  Grid<2>::octave_output(std::ostream& os) const
  {
    os << "x = "<< gridx_;
//     os << ";" << std::endl;
    
    os << "y = "<<gridy_;
//     os << ";" << std::endl;
  }
  
}
  
