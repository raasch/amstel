// implementation of some (inline) Array2D<C>:: methods

#include <cassert>
#include <algorithm>
#include <iomanip>
#include "io/matrix_io.h"

namespace AMSTeL
{
  template <class C>
  inline
  Array2D<C>::Array2D()
    : data_(0), size_(0), coldim_(0), rowdim_(0)
  {
  }

  template <class C>
  inline
  Array2D<C>::Array2D(const size_type s)
    : size_(s*s),coldim_(s),rowdim_(s)
  {
    if (s == 0)
      data_ = 0;
    else
      {
        data_ = new C[s*s]; // calls C()
      }
  }

  template <class C>
  inline
  Array2D<C>::Array2D(const size_type row,const size_type col)
    : size_(col*row),coldim_(col),rowdim_(row)
  {
    if (col*row == 0)
      data_ = 0;
    else
      {
        data_ = new C[col*row]; // calls C()
      }
  }

  template <class C>
  inline
  Array2D<C>::Array2D(const Array2D<C>& a)
    : size_(a.size()),rowdim_(a.rowdim_), coldim_(a.coldim_)
  {
    if (size_ == 0)
      data_ = 0;
    else
      {
        data_ = new C[size_];
        std::copy(a.begin(), a.end(), begin());
      }
  }

  template <class C>
  Array2D<C>& Array2D<C>::operator = (const Array2D<C>& a)
  {
    resize(a.row_dimension(), a.column_dimension());
    std::copy(a.begin(), a.end(), begin());
    rowdim_=a.rowdim_;
    coldim_=a.coldim_;

    return *this;
  }

  template <class C>
  inline
  Array2D<C>::~Array2D()
  {
    if (data_ != 0) delete [] data_;
    size_ = 0;
    rowdim_=0;
    coldim_=0;
  }
  
  template <class C>
  inline
  const typename Array2D<C>::size_type
  Array2D<C>::size() const
  {
    return size_;
  }

  template <class C>
  void Array2D<C>::resize(const size_type row,const size_type col)
  {
    rowdim_= row;
    coldim_= col;
    size_type s=col*row;
    if (s == 0)
      {
        if (data_ != 0) {
          delete [] data_;
          data_ = 0;
        }
      	size_ = 0;
      }
    else
      {
        if (size_ != s) {
          if (data_ != 0) delete [] data_;
          data_ = new C[s]; // calls C()
          size_ = s;
        }
      }
  }

  template <class C>
  inline
  const C& Array2D<C>::operator () (const size_type row, const size_type col) const
  { 
    assert(row < rowdim_);
    assert(col < coldim_);
    return data_[row+col*rowdim_];
  }

  template <class C>
  inline
  C& Array2D<C>::operator () (const size_type row, const size_type col)
  {
    assert(row < rowdim_);
    assert(col < coldim_);
    return data_[row+col*rowdim_];
  }

  template <class C>
  inline
  typename Array2D<C>::const_iterator
  Array2D<C>::begin() const
  {
    return &data_[0];
  }

  template <class C>
  inline
  typename Array2D<C>::iterator
  Array2D<C>::begin()
  {
    return &data_[0];
  }

  template <class C>
  inline
  typename Array2D<C>::const_iterator
  Array2D<C>::end() const
  {
    return &data_[size_];
  }

  template <class C>
  inline
  typename Array2D<C>::iterator
  Array2D<C>::end()
  {
    return &data_[size_];
  }

  template <class C>
  inline
  void Array2D<C>::swap(Array2D<C>& a)
  {
    std::swap(rowdim_, a.rowdim_);
    std::swap(coldim_, a.coldim_);
    std::swap(data_, a.data_);
  }

  template <class C>
  inline
  const typename Array2D<C>::size_type
  Array2D<C>::row_dimension() const
  {
    return rowdim_;
  }

  template <class C>
  inline
  const typename Array2D<C>::size_type
  Array2D<C>::column_dimension() const
  {
    return coldim_;
  }

  template <class C>
  inline
  std::ostream& operator << (std::ostream& os, const Array2D<C>& a)
  {
    // use generic matrix print routine
    print_matrix(a, os);
    return os;
  }

}
