// implementation for sampled_mapping.h
namespace AMSTeL
{
  template <class C>
  SampledMapping<1,C>::SampledMapping()
    : Grid<1>(), values_()
  {
  }

  template <class C>
  SampledMapping<1,C>::SampledMapping(const SampledMapping<1,C>& sm)
    : Grid<1>(sm), values_(sm.values_)
  {
  }

  template <class C>
  SampledMapping<1,C>::SampledMapping(const Grid<1>& grid)
    : Grid<1>(grid), values_(grid.size())
  {
    for (unsigned int i = 0; i < grid.size(); i++)
      values_[i] = 0;
  }

  template <class C>
  SampledMapping<1,C>::SampledMapping(const Grid<1>& grid, const Array1D<C>& values)
    : Grid<1>(grid), values_(values)
  {
  }

  template <class C>
  SampledMapping<1,C>::SampledMapping(const int a,
				      const int b,
				      const InfiniteVector<C, int>& values,
				      const int resolution)
    : Grid<1>(a, b, (1<<resolution)*(b-a))
  {
    values_.resize(Grid<1>::size());
    for (int k(a<<resolution), n(0); k <= (b<<resolution); k++, n++)
      values_[n] = values.get_coefficient(k);
  }
  
  template <class C>
  SampledMapping<1,C>& 
  SampledMapping<1,C>::operator = (const SampledMapping<1,C>& sm)
  {
    Grid<1>::operator = (sm);
    values_ = sm.values_;
    return *this;
  }
  
  template <class C>
  void
  SampledMapping<1,C>::add(const SampledMapping<1,C>& s)
  {
    assert(values_.size() == s.values_.size());
    for (unsigned int i = 0; i < values_.size(); i++)
      values_[i] += s.values_[i];
  }

  template <class C>
  void
  SampledMapping<1,C>::add(const C alpha, const SampledMapping<1,C>& s)
  {
    assert(values_.size() == s.values_.size());
    for (unsigned int i = 0; i < values_.size(); i++)
      values_[i] += alpha * s.values_[i];
  }

  template <class C>
  void
  SampledMapping<1,C>::mult(const C alpha)
  {
    for (unsigned int i = 0; i < values_.size(); i++)
      values_[i] *= alpha;
  }

  template <class C>
  void
  SampledMapping<1,C>::matlab_output(std::ostream& os,
				     bool add_plot_command) const
  {
    Grid<1>::matlab_output(os);
    os << "y = " // here we can take y
       << values_
       << ";"
       << std::endl;

    if (add_plot_command)
      os << "plot(x,y)\n" << std::endl;
  }

  template <class C>
  void
  SampledMapping<1,C>::gnuplot_output(std::ostream& os) const
  {
    unsigned int i;
    const unsigned int size = grid_.size();
    assert(values_.size() == size); // sizes of arrays must match

    for (i = 0; i < size; i++) // loop through entries
      os << grid_[i] << "\t" << values_[i] << std::endl; // format: one value pair per row, in each row x y
  }

  template <class C>
  SampledMapping<2,C>::SampledMapping()
    : Grid<2>(), values_()
  {
  }

  template <class C>
  SampledMapping<2,C>::SampledMapping(const SampledMapping<2,C>& sm)
    : Grid<2>(sm), values_(sm.values_)
  {
  }

  template <class C>
  SampledMapping<2,C>::SampledMapping(const Grid<2>& grid)
    : Grid<2>(grid)
  {
    values_.resize(gridx_.row_dimension(), gridx_.column_dimension());
  }

  template <class C>
  SampledMapping<2,C>::SampledMapping(const Grid<2>& grid, const Array2D<C>& values)
    : Grid<2>(grid), values_(values)
  {
  }

  template <class C>
  SampledMapping<2,C>&
  SampledMapping<2,C>::operator = (const SampledMapping<2,C>& sm)
  {
    Grid<2>::operator = (sm);
    values_ = sm.values_;
    return *this;
  }

  template <class C>
  void
  SampledMapping<2,C>::add(const SampledMapping<2,C>& s)
  {
    assert(values_.row_dimension() == s.values_.row_dimension()
	   && values_.column_dimension() == s.values_.column_dimension());
    for (unsigned int m(0); m < values_.row_dimension(); m++)
      for (unsigned int n(0); n < values_.column_dimension(); n++)
	values_(m,n) += s.values_(m,n);
  }

  template <class C>
  void
  SampledMapping<2,C>::add(const C alpha, const SampledMapping<2,C>& s)
  {
    assert(values_.row_dimension() == s.values_.row_dimension()
	   && values_.column_dimension() == s.values_.column_dimension());
    for (unsigned int m(0); m < values_.row_dimension(); m++)
      for (unsigned int n(0); n < values_.column_dimension(); n++)
	values_(m,n) += alpha * s.values_(m,n);
  }
  
  template <class C>
  void
  SampledMapping<2,C>::add(const Array2D<C>& mat)
  {
    assert(values_.row_dimension() == mat.row_dimension()
	   && values_.column_dimension() == mat.column_dimension());
    for (unsigned int m(0); m < values_.row_dimension(); m++)
      for (unsigned int n(0); n < values_.column_dimension(); n++)
	values_(m,n) += mat(m,n);
  }
  
  template <class C>
  void
  SampledMapping<2,C>::add(const C alpha, const Array2D<C>& mat)
  {
    assert(values_.row_dimension() == mat.row_dimension()
	   && values_.column_dimension() == mat.column_dimension());
    for (unsigned int m(0); m < values_.row_dimension(); m++)
      for (unsigned int n(0); n < values_.column_dimension(); n++)
	values_(m,n) += alpha * mat(m,n);
  }

  template <class C>
  void
  SampledMapping<2,C>::mult(const C alpha)
  {
    for (unsigned int m(0); m < values_.row_dimension(); m++)
      for (unsigned int n(0); n < values_.column_dimension(); n++)
	values_(m,n) *= alpha;    
  }

  template <class C>
  void
  SampledMapping<2,C>::matlab_output(std::ostream& os,
				     bool add_plot_command) const
  {
    Grid<2>::matlab_output(os);
    os << "z = ";
    os << values_;
    os << ";"
       << std::endl;

    if (add_plot_command)
      os << "surf(x,y,z)\n" << std::endl;
  }

  template <class C>
  void
  SampledMapping<2,C>::gnuplot_output(std::ostream& os) const
  {
    
    
    for (int i = 0; i < gridy_.row_dimension(); i++) {
      for (int j = 0; j < gridx_.column_dimension(); j++) {
	os << gridx_(i,j) << "\t" << gridy_(i,j) << "\t" << values_(i,j) << endl;
      }
    }
  }

  template <class C>
  void
  SampledMapping<2,C>::octave_output(std::ostream& os) const
  {
    Grid<2>::octave_output(os);
    os << "z = ";
    os<< values_;
//     os << ";"
//        << std::endl;
  }

  template <unsigned int DIM, class C>
  void matlab_output(std::ostream& os,
		     const SampledMapping<DIM,C>& sm)
  {
    os << "figure\n" << std::endl;
    sm.matlab_output(os, true);
  }
  
  template <unsigned int DIM, class C>
  void matlab_output(std::ostream& os,
		     const Array1D<SampledMapping<DIM,C> >& values)
  {
    os << "figure\n" << std::endl;
    os << "hold on\n" << std::endl;
    
    for (unsigned int i = 0; i < values.size(); i++) {
      values[i].matlab_output(os, true);
    }
    os << "hold off\n" << std::endl;
  }

  template <unsigned int DIM, class C>
  void gnuplot_output(std::ostream& os,
		      const Array1D<SampledMapping<DIM,C> >& values)
  {
    switch (DIM) {
    case 1: {
      for (unsigned int i = 0; i < values.size(); i++) {
	values[i].gnuplot_output(os);
      }
      break;
    }
    case 2: {
      for (unsigned int i = 0; i < values.size(); i++) {
	values[i].gnuplot_output(os);
      }
      break;
    }      
    }// end switch

  }


  template <unsigned int DIM, class C>
  void octave_output(std::ostream& os,
		     const Array1D<SampledMapping<DIM,C> >& values)
  {
    assert(DIM==2);

    for (unsigned int i = 0; i < values.size(); i++) {
      values[i].octave_output(os);
      os << "hold on" << std::endl
	 << "mesh(x,y,z)" << std::endl;
      if (i == (values.size()-1))
	os << "hold off" << std::endl;
    }
  };
  
}