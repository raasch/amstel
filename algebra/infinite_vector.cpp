// implementation of InfiniteVector inline functions

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <type_traits>

#include "infinite_vector.h"

using std::cout;
using std::endl;

namespace AMSTeL
{
  // implementation of InfiniteVector member functions
  
  template <class C, class I, class CONTAINER>
  InfiniteVector<C,I,CONTAINER>::InfiniteVector()
    : CONTAINER()
  {
  }

  template <class C, class I, class CONTAINER>
  InfiniteVector<C,I,CONTAINER>::InfiniteVector(const InfiniteVector<C,I,CONTAINER>& v)
    : CONTAINER(v)
  {
  }

  template <class C, class I, class CONTAINER>
  inline
  typename InfiniteVector<C,I,CONTAINER>::const_iterator
  InfiniteVector<C,I,CONTAINER>::begin() const
  {
    return const_iterator(*this, CONTAINER::begin());
  }
  
  template <class C, class I, class CONTAINER>
  inline
  typename InfiniteVector<C,I,CONTAINER>::const_iterator
  InfiniteVector<C,I,CONTAINER>::end() const
  {
    return const_iterator(*this, CONTAINER::end());
  }
  
  template <class C, class I, class CONTAINER>
  InfiniteVector<C,I,CONTAINER>&
  InfiniteVector<C,I,CONTAINER>::operator = (const InfiniteVector<C,I,CONTAINER>& v)
  {
    CONTAINER::operator = (v);
    return *this;
  }
  
  template <class C, class I, class CONTAINER>
  inline
  void InfiniteVector<C,I,CONTAINER>::swap(InfiniteVector<C,I,CONTAINER>& v)
  {
    CONTAINER::swap(v);
  }

  template <class C, class I, class CONTAINER>
  inline
  void InfiniteVector<C,I,CONTAINER>::clear()
  {
    CONTAINER::clear();
  }
  
  template <class C, class I, class CONTAINER>
  inline
  bool
  InfiniteVector<C,I,CONTAINER>::operator == (const InfiniteVector<C,I,CONTAINER>& v) const
  {
#if 1
    // this implementation is desirable (using code from <algorithm>),
    // but did not compile under macOS until modifying InfiniteVectorConstIterator::operator *
    return (size()==v.size()) && std::equal(this->begin(), this->end(), v.begin());
#else
    const_iterator it(begin()), itend(end()), vit(v.begin()), vend(v.end());
      do {
          if (it==itend)
              return vit==vend;
          if (vit==vend)
              return false;
      } while (*it++ == *vit++);
      return false;
#endif
  }

  template <class C, class I, class CONTAINER>
  inline
  bool
  InfiniteVector<C,I,CONTAINER>::operator != (const InfiniteVector<C,I,CONTAINER>& v) const
  {
    return !((*this) == v);
  }

  template <class C, class I, class CONTAINER>
  inline
  C InfiniteVector<C,I,CONTAINER>::operator [] (const I& index) const
  {
    return get_coefficient(index);
  }

  template <class C, class I, class CONTAINER>
  C InfiniteVector<C,I,CONTAINER>::get_coefficient(const I& index) const
  {
    // note: the following code, avoiding explicit specializations, will only compile in C++17 and onwards
    if constexpr (std::is_same_v<std::unordered_map<I,C>, CONTAINER>)
    {
      // specialization for unordered container classes like std::unordered_map
      typename CONTAINER::const_iterator it(this->find(index));
      if (it != CONTAINER::end())
        return it->second;
    }
    else
    {
      // generic code for ordered container classes like std::map
      typename CONTAINER::const_iterator it(this->lower_bound(index));
      if (it != CONTAINER::end())
      {
        if (!CONTAINER::key_comp()(index, it->first))
          return it->second;
      }
    }
    return C(0);
  }

  template <class C, class I, class CONTAINER>
  C& InfiniteVector<C,I,CONTAINER>::operator [] (const I& index)
  {
  // note: the following code, avoiding explicit specializations, will only compile in C++17 and onwards
    if constexpr (std::is_same_v<std::unordered_map<I,C>, CONTAINER>)
    {
      typename CONTAINER::iterator it(this->find(index));
      if (it != CONTAINER::end())
        return it->second;
      else
        return CONTAINER::insert(it, typename CONTAINER::value_type(index, C(0)))->second;
    }
    else
    {
      // generic code for ordered container classes like std::map
      // efficient add-or-update, cf. Meyers, Effective STL
      typename CONTAINER::iterator it(this->lower_bound(index));
      if (it != CONTAINER::end() &&
          !CONTAINER::key_comp()(index, it->first))
        return it->second;
      else
        return CONTAINER::insert(it, typename CONTAINER::value_type(index, C(0)))->second;
        // alternative: return CONTAINER::insert(typename CONTAINER::value_type(index, C(0))).first->second;
    }
  }

  template <class C, class I, class CONTAINER>
  void InfiniteVector<C,I,CONTAINER>::set_coefficient(const I& index, const C value)
  {
  // note: the following code, avoiding explicit specializations, will only compile in C++17 and onwards
    if constexpr (std::is_same_v<std::unordered_map<I,C>, CONTAINER>)
    {
      typename CONTAINER::iterator it(this->find(index));
      if (it != CONTAINER::end())
        it->second = value;
      else
        CONTAINER::insert(it, typename CONTAINER::value_type(index, value));
    }
    else
    {
      // generic code for ordered container classes like std::map
      typename CONTAINER::iterator it(this->lower_bound(index));
      if (it != CONTAINER::end() &&
          !CONTAINER::key_comp()(index,it->first)) {
        it->second = value;
      }
      else {
        CONTAINER::insert(it, typename CONTAINER::value_type(index, value));
        //CONTAINER::insert(typename CONTAINER::value_type(index, value));
      }
    }
  }

  template <class C, class I, class CONTAINER>
  inline
  size_t InfiniteVector<C,I,CONTAINER>::size() const
  {
    return CONTAINER::size();
  }
  
  template <class C, class I, class CONTAINER>
  void
  InfiniteVector<C,I,CONTAINER>::support(std::set<I>& supp) const
  {
    supp.clear();
    for (const_iterator it(begin()), itend(end()); it != itend; ++it)
      supp.insert(supp.end(), it.index());
  }

  template <class C, class I, class CONTAINER>
  void
  InfiniteVector<C,I,CONTAINER>::clip(const std::set<I>& supp)
  {
    CONTAINER v;

    const_iterator it(begin()), itend(end());
    typename std::set<I>::const_iterator suppit(supp.begin()), suppend(supp.end());
    for (; it != itend && suppit != suppend; ++it)
      {
        while (suppit != suppend && *suppit < it.index()) ++suppit;
        if (*suppit == it.index())
          v.insert(v.end(), std::pair<I,C>(it.index(), it.value()));
      }

    CONTAINER::swap(v);
  }

//  template <class C, class I>
//  void InfiniteVector<C,I>::compress(const double eta)
//  {
//    // a hardcore STL implementation inspired by Meyers, Effective STL:
//    CONTAINER v;
//    std::remove_copy_if(CONTAINER::begin(),
//                        CONTAINER::end(),
//                        std::inserter(v, v.end()),
//                        threshold_criterion<I,C>(eta));
//    CONTAINER::swap(v);
//  }
//
//  template <class C, class I>
//  void InfiniteVector<C,I>::shrinkage(const double mu)
//  {
//    compress(mu);
//    // a hardcore STL implementation inspired by Meyers, Effective STL:
//    for (typename InfiniteVector<C,I>::const_iterator it(begin()),
//         itend(end()); it != itend; ++it){
//      //        if(*it<=mu)
//      //            CONTAINER::erase(it.index());
//      if(*it>mu)
//        set_coefficient(it.index(), *it-0.5*mu);
//      if(*it < -mu)
//        set_coefficient(it.index(), *it+0.5*mu);
//    }
//  }
  
  template <class C, class I, class CONTAINER>
  void InfiniteVector<C,I,CONTAINER>::add_coefficient(const I& index, const C increment)
  {
  // note: the following code, avoiding explicit specializations, will only compile in C++17 and onwards
    if constexpr (std::is_same_v<std::unordered_map<I,C>, CONTAINER>)
    {
      typename CONTAINER::iterator it(this->find(index));
      if (it != CONTAINER::end())
      {
        if ((it->second += increment) == C(0))
          CONTAINER::erase(it);
        }
      else {
        // insert the increment as new coefficient
        CONTAINER::insert(it, typename CONTAINER::value_type(index, increment));
      }
    }
    else
    {
      // generic code for ordered container classes like std::map
      // efficient add-or-update, cf. Meyers, Effective STL
      typename CONTAINER::iterator it(this->lower_bound(index));
      if (it != CONTAINER::end() &&
        !CONTAINER::key_comp()(index, it->first))
      {
        // we already have a nontrivial coefficient
        if ((it->second += increment) == C(0))
          CONTAINER::erase(it);
      } else {
        // insert the increment as new coefficient
        CONTAINER::insert(it, typename CONTAINER::value_type(index, increment));
      }
    }
  }
  
  template <class C, class I, class CONTAINER>
  void InfiniteVector<C,I,CONTAINER>::add(const InfiniteVector<C,I,CONTAINER>& v)
  {
#if 1
    CONTAINER help;

    // The following O(N) algorithm is adapted from the STL algorithm set_union(),
    // cf. stl_algo.h ...

    typename InfiniteVector<C,I,CONTAINER>::const_iterator it(begin()), itend(end()),
      itv(v.begin()), itvend(v.end());
    typename CONTAINER::iterator hint(help.begin()), hint2(help.begin());

    while (it != itend && itv != itvend)
      {
        if (it.index() < itv.index())
        {
          hint2 = help.insert(hint, std::pair<I,C>(it.index(), it.value()));
          hint = hint2;
          ++it;
        }
        else
        {
          if (itv.index() < it.index())
          {
            hint2 = help.insert(hint, std::pair<I,C>(itv.index(), itv.value()));
            hint = hint2;
            ++itv;
          }
          else
          {
            const C value(it.value() + itv.value());
            if (value != C(0)) {
              hint2 = help.insert(hint, std::pair<I,C>(itv.index(), value));
              hint = hint2;
            }
            ++it;
            ++itv;
          }
        }
      }

    while (it != itend)
      {
        hint2 = help.insert(hint, std::pair<I,C>(it.index(), it.value()));
        hint = hint2;
        ++it;
      }

    while (itv != itvend)
    {
      hint2 = help.insert(hint, std::pair<I,C>(itv.index(), itv.value()));
      hint = hint2;
      ++itv;
    }

    CONTAINER::swap(help);
#else
    // the following code can be optimized (not O(N) now)
    typename InfiniteVector<C,I,CONTAINER>::const_iterator itv(v.begin()), itvend(v.end());
    for (; itv != itvend; ++itv)
      {
        C help(get_coefficient(itv.index()) + itv.value());

        if (help != C(0))
          set_coefficient(itv.index(), help);
        else
          CONTAINER::erase(itv.index());
      }
#endif
  }

  template <class C, class I, class CONTAINER>
  void InfiniteVector<C,I,CONTAINER>::add(const C s, const InfiniteVector<C,I,CONTAINER>& v)
  {
#if 1
    CONTAINER help;

    // The following O(N) algorithm is adapted from the STL algorithm set_union(),
    // cf. stl_algo.h ...

    typename InfiniteVector<C,I,CONTAINER>::const_iterator it(begin()), itend(end()),
      itv(v.begin()), itvend(v.end());
    typename CONTAINER::iterator hint(help.begin()), hint2(help.begin());

    while (it != itend && itv != itvend)
      {
        if (it.index() < itv.index())
        {
          hint2 = help.insert(hint, std::pair<I,C>(it.index(), it.value()));
          hint = hint2;
          ++it;
        }
        else
        {
          if (itv.index() < it.index())
          {
            hint2 = help.insert(hint, std::pair<I,C>(itv.index(), s * itv.value()));
            hint = hint2;
            ++itv;
          }
          else
          {
            const C value(it.value() + s * itv.value());
            if (value != C(0)) {
              hint2 = help.insert(hint, std::pair<I,C>(itv.index(), value));
              hint = hint2;
            }
            ++it;
            ++itv;
          }
        }
      }

    while (it != itend)
      {
        hint2 = help.insert(hint, std::pair<I,C>(it.index(), it.value()));
        hint = hint2;
        ++it;
      }

    while (itv != itvend)
      {
        hint2 = help.insert(hint, std::pair<I,C>(itv.index(), s * itv.value()));
        hint = hint2;
        ++itv;
      }

    CONTAINER::swap(help);
#else
    // the following code can be optimized (not O(N) now)
    typename InfiniteVector<C,I,CONTAINER>::const_iterator itv(v.begin()), itvend(v.end());
    for (; itv != itvend; ++itv)
      {
        C help(get_coefficient(itv.index()) + s * itv.value());
        if (help != C(0))
          set_coefficient(itv.index(), help);
        else
          CONTAINER::erase(itv.index());
      }
#endif
  }

  template <class C, class I, class CONTAINER>
  void InfiniteVector<C,I,CONTAINER>::sadd(const C s, const InfiniteVector<C,I,CONTAINER>& v)
  {
#if 1
    CONTAINER help;

    // The following O(N) algorithm is adapted from the STL algorithm set_union(),
    // cf. stl_algo.h ...

    typename InfiniteVector<C,I,CONTAINER>::const_iterator it(begin()), itend(end()),
      itv(v.begin()), itvend(v.end());
    typename CONTAINER::iterator hint(help.begin()), hint2(help.begin());

    while (it != itend && itv != itvend)
      {
        if (it.index() < itv.index())
        {
          hint2 = help.insert(hint, std::pair<I,C>(it.index(), s * it.value()));
          hint = hint2;
          ++it;
        }
        else
        {
          if (itv.index() < it.index())
          {
            hint2 = help.insert(hint, std::pair<I,C>(itv.index(), itv.value()));
            hint = hint2;
            ++itv;
          }
          else
          {
            const C value(s * it.value() + itv.value());
            if (value != C(0))
            {
              hint2 = help.insert(hint, std::pair<I,C>(itv.index(), value));
              hint = hint2;
            }
            ++it;
            ++itv;
          }
        }
      }

    while (it != itend)
      {
        hint2 = help.insert(hint, std::pair<I,C>(it.index(), s * it.value()));
        hint = hint2;
        ++it;
      }

    while (itv != itvend)
      {
        hint2 = help.insert(hint, std::pair<I,C>(itv.index(), itv.value()));
        hint = hint2;
        ++itv;
      }

    CONTAINER::swap(help);
#else
    // the following code can be optimized (not O(N) now)
    typename InfiniteVector<C,I,CONTAINER>::const_iterator itv(v.begin()), itvend(v.end());
    for (; itv != itvend; ++itv)
      {
        C help(s * get_coefficient(itv.index()) + itv.value());
        if (help != C(0))
          set_coefficient(itv.index(), help);
        else
          CONTAINER::erase(itv.index());
      }
#endif
  }

  template <class C, class I, class CONTAINER>
  void InfiniteVector<C,I,CONTAINER>::scale(const C s)
  {
    if (s == C(0))
      clear();
    else
      {
        typename CONTAINER::iterator it(CONTAINER::begin()),
        itend(CONTAINER::end());
        while(it != itend)
          (*it++).second *= s;
      }
  }

  template <class C, class I, class CONTAINER>
  inline
  InfiniteVector<C,I,CONTAINER>& InfiniteVector<C,I,CONTAINER>::operator += (const InfiniteVector<C,I,CONTAINER>& v)
  {
    add(v);
    return *this;
  }

  template <class C, class I, class CONTAINER>
  void InfiniteVector<C,I,CONTAINER>::subtract(const InfiniteVector<C,I,CONTAINER>& v)
  {
#if 1
    CONTAINER help;

    // The following O(N) algorithm is adapted from the STL algorithm set_union(),
    // cf. stl_algo.h ...

    typename InfiniteVector<C,I,CONTAINER>::const_iterator it(begin()), itend(end()),
      itv(v.begin()), itvend(v.end());
    typename CONTAINER::iterator hint(help.begin()), hint2(help.begin());

    while (it != itend && itv != itvend)
      {
        if (it.index() < itv.index())
        {
          hint2 = help.insert(hint, std::pair<I,C>(it.index(), it.value()));
          hint = hint2;
          ++it;
        }
        else
        {
          if (itv.index() < it.index())
          {
            hint2 = help.insert(hint, std::pair<I,C>(itv.index(), -itv.value()));
            hint = hint2;
            ++itv;
          }
          else
          {
            const C value(it.value() - itv.value());
            if (value != C(0))
            {
              hint2 = help.insert(hint, std::pair<I,C>(itv.index(), value));
              hint = hint2;
            }
            ++it;
            ++itv;
          }
        }
      }

    while (it != itend)
      {
        hint2 = help.insert(hint, std::pair<I,C>(it.index(), it.value()));
        hint = hint2;
        ++it;
      }

    while (itv != itvend)
      {
        hint2 = help.insert(hint, std::pair<I,C>(itv.index(), -itv.value()));
        hint = hint2;
        ++itv;
      }

    CONTAINER::swap(help);
#else
    // the following code can be optimized (not O(N) now)
    typename InfiniteVector<C,I,CONTAINER>::const_iterator itv(v.begin()), itvend(v.end());
    for (; itv != itvend; ++itv)
      {
        C help(get_coefficient(itv.index()) - itv.value());
        if (help != C(0))
          set_coefficient(itv.index(), help);
        else
          CONTAINER::erase(itv.index());
      }
#endif
  }

  template <class C, class I, class CONTAINER>
  inline
  InfiniteVector<C,I,CONTAINER>& InfiniteVector<C,I,CONTAINER>::operator -= (const InfiniteVector<C,I,CONTAINER>& v)
  {
    subtract(v);
    return *this;
  }
   
  template <class C, class I, class CONTAINER>
  InfiniteVector<C,I,CONTAINER>& InfiniteVector<C,I,CONTAINER>::operator *= (const C s)
  {
    scale(s);
    return *this;
  }

  template <class C, class I, class CONTAINER>
  InfiniteVector<C,I,CONTAINER>& InfiniteVector<C,I,CONTAINER>::operator /= (const C s)
  {
    // we don't catch the division by zero exception here!
    return (*this *= 1.0/s);
  }

  template <class C, class I, class CONTAINER>
  const C InfiniteVector<C,I,CONTAINER>::operator * (const InfiniteVector<C,I,CONTAINER>& v) const
  {
    if (this == reinterpret_cast<const InfiniteVector<C,I,CONTAINER>*>(&v))
      return l2_norm_sqr(*this);

    C r(0);
    
    for (typename InfiniteVector<C,I,CONTAINER>::const_iterator
         it(begin()),
         itend(end()),
         itv(v.begin()),
         itvend(v.end());
         it != itend && itv != itvend; ++it)
    {
      while (itv != itvend && itv.index() < it.index()) ++itv;
      if (itv != itvend)
        if (it.index() == itv.index())
          r += it.value() * itv.value();
    }

    return r;
  }

  template <class C, class I, class CONTAINER>
  double operator * (const InfiniteVector<C,I,CONTAINER>& v, const InfiniteVector<C,I,CONTAINER>& w)
  {
    double r(0);
    typedef typename InfiniteVector<C,I,CONTAINER>::const_iterator const_iterator;
    const_iterator itv(v.begin()), itvend(v.end()), itw(w.begin()), itwend(w.end());
    for (; itv != itvend && itw != itwend; ++itv)
      {
        while (itw != itwend && itw.index() < itv.index()) ++itw;
        if (itv.index() == itw.index())
          r += itw.value() * itv.value();
      }
    return r;
  }

  template <class C, class I, class CONTAINER>
  double InfiniteVector<C,I,CONTAINER>::weak_norm(const double tau) const
  {
    double r(0.0);

    if (size() > 0)
      {
        // prepare vector to be sorted
        std::vector<std::pair<I,C> > sv(size());
        unsigned int id(0);
        for (const_iterator it(begin()), itend(end());
             it != itend; ++it, ++id)
        {
          sv[id] = std::pair<I, C>(it.index(), it.value()); // can't use make_pair for gcc 2.95
        }
	  
        // sort vector (Introsort, O(N*log N))
        sort(sv.begin(), sv.end(), decreasing_order());
	  
        // compute \|*this\|_{\ell^w_\tau}:=\sup_{N=1}^\infty N^{1/tau}|v_N^*|
        // where the v_N^* are the decreasing rearrangement of me
        for (unsigned int N(1); N <= sv.size(); N++)
          r = std::max(r, pow(N, 1.0/tau) * fabs(sv[N-1].second));
      }

    return r;
  }

  template <class C, class I, class CONTAINER>
  void InfiniteVector<C,I,CONTAINER>::COARSE(const double eps, InfiniteVector<C,I,CONTAINER>& v) const
  {
    // We use a straightforward implementation with complexity O(N*log(N)):
    // - sort my entries in modulus
    //   1. possibility: use a helper multimap object
    //   2. possibility: use a sorted vector (preferred solution, since no
    //                   slow insertion sort algorithm is launched!)
    // - insert the largest in modulus entries into v until
    //     \|*this-v\|_{\ell_2}\le\epsilon
    //
    // Another possibility would be binary binning, which we will implement
    // in a later stage of the library!

    v.clear();
    if (size() > 0) {
      if (eps == 0)
        v = *this;
      else
      {
        // prepare vector to be sorted
        std::vector<std::pair<I,C> > sv(size());

        //abort();
        unsigned int id(0);
        for (const_iterator it(begin()), itend(end()); it != itend; ++it, ++id) {
          sv[id] = std::pair<I,C>(it.index(), it.value()); // can't use make_pair for gcc 2.95
        }

        // sort vector (Introsort, O(N*log N))
        sort(sv.begin(), sv.end(), decreasing_order());
        
        // insert largest in modulus entries until tolerance is reached
        double coarsenorm(0);
        double nrm(l2_norm(*this));
        double bound(nrm*nrm - eps*eps);
        typename std::vector<std::pair<I,C> >::iterator it(sv.begin());
        do
        {
          coarsenorm += it->second * it->second;
          ++it;
        }
        while ((it != sv.end()) && (coarsenorm < bound));
        sv.erase(it, sv.end());

        // insert relevant entries in v (-> insertion sort, we hope that
        // the number of entries is neglectible)
        for (unsigned int i(0); i < sv.size(); i++)
          v.set_coefficient(sv[i].first, sv[i].second);
      }
    }
  }

  template <class C, class I, class CONTAINER>
  const double
  InfiniteVector<C,I,CONTAINER>::wrmsqr_norm(const double atol, const double rtol,
				   const InfiniteVector<C,I,CONTAINER>& v, const InfiniteVector<C,I,CONTAINER>& w) const
  {
    double result = 0;
    
    for (const_iterator it(begin()), itend(end());
         it != itend; ++it)
      {
        const double help = it.value() /
          (atol + rtol * std::max(fabs(v.get_coefficient(it.index())),
                                  fabs(w.get_coefficient(it.index()))));
        result += help * help;
      }

    return result == 0 ? 0 : sqrt(result/size());
  }

  //
  // implementation of InfiniteVector::const_iterator class

  template <class C, class I, class CONTAINER>
  InfiniteVectorConstIterator<C,I,CONTAINER>::InfiniteVectorConstIterator
    (const InfiniteVector<C,I,CONTAINER>& container,
     const typename CONTAINER::const_iterator& position)
  : CONTAINER::const_iterator(position), _container(container)
  {
  }

  template <class C, class I, class CONTAINER>
  inline
  const typename InfiniteVectorConstIterator<C,I,CONTAINER>::reference
  InfiniteVectorConstIterator<C,I,CONTAINER>::operator * () const
  {
    return CONTAINER::const_iterator::operator * ();
  }

  template <class C, class I, class CONTAINER>
  inline
  const typename InfiniteVectorConstIterator<C,I,CONTAINER>::pointer
  InfiniteVectorConstIterator<C,I,CONTAINER>::operator -> () const
  {
    return CONTAINER::const_iterator::operator -> ();
  }

  template <class C, class I, class CONTAINER>
  inline
  const I&
  InfiniteVectorConstIterator<C,I,CONTAINER>::index() const
  {
    return (CONTAINER::const_iterator::operator *()).first;
  }

  template <class C, class I, class CONTAINER>
  inline
  const C
  InfiniteVectorConstIterator<C,I,CONTAINER>::value() const
  {
    return (CONTAINER::const_iterator::operator *()).second;
  }
  
  template <class C, class I, class CONTAINER>
  inline
  bool
  InfiniteVectorConstIterator<C,I,CONTAINER>::
  operator == (const InfiniteVectorConstIterator<C,I,CONTAINER>& it) const
  {
    return (static_cast<typename CONTAINER::const_iterator>(*this)
            == static_cast<typename CONTAINER::const_iterator>(it));
  }
  
  template <class C, class I, class CONTAINER>
  inline
  bool
  InfiniteVectorConstIterator<C,I,CONTAINER>::
  operator != (const InfiniteVectorConstIterator<C,I,CONTAINER>& it) const
  {
    return !(*this == it);
  }
  
  template <class C, class I, class CONTAINER>
  inline
  bool
  InfiniteVectorConstIterator<C,I,CONTAINER>::
  operator < (const InfiniteVectorConstIterator<C,I,CONTAINER>& it) const
  {
    return (index() < it.index());
  }
  
  template <class C, class I, class CONTAINER>
  inline
  InfiniteVectorConstIterator<C,I,CONTAINER>&
  InfiniteVectorConstIterator<C,I,CONTAINER>::operator ++ ()
  {
    CONTAINER::const_iterator::operator ++ ();
    return *this;
  }

  template <class C, class I, class CONTAINER>
  inline
  InfiniteVectorConstIterator<C,I,CONTAINER>
  InfiniteVectorConstIterator<C,I,CONTAINER>::operator ++ (int step)
  {
    InfiniteVectorConstIterator<C,I,CONTAINER> r(*this);
    CONTAINER::const_iterator::operator ++ (step);
    return r;
  }

  // implementation of external InfiniteVector functionality
  
  template <class C, class I, class CONTAINER>
  inline
  void swap(InfiniteVector<C,I,CONTAINER>& v1, InfiniteVector<C,I,CONTAINER>& v2)
  {
    v1.swap(v2);
  }

  template <class C, class I, class CONTAINER>
  std::ostream& operator << (std::ostream& os,
			     const InfiniteVector<C,I,CONTAINER>& v)
  {
    if (v.begin() ==  v.end())
      {
        os << "0";
      }
    else
      {
        for (typename InfiniteVector<C,I,CONTAINER>::const_iterator it(v.begin());
             it != v.end(); ++it)
        {
          os << it.index() << ": " << it.value() << std::endl;
        }
      }

    return os;
  }
}
