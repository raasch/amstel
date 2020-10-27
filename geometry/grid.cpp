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
  
  /*
  grid<2> will be added later
*/
  
}
