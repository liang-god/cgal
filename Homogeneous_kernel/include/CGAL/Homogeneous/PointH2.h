// Copyright (c) 1999  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
//
//
// Author(s)     : Stefan Schirra

#ifndef CGAL_HOMOGENEOUS_POINT_2_H
#define CGAL_HOMOGENEOUS_POINT_2_H

#include <CGAL/Origin.h>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/utility.hpp>

CGAL_BEGIN_NAMESPACE

template < class R_ >
class PointH2
{
  typedef typename R_::FT                   FT;
  typedef typename R_::RT                   RT;
  typedef typename R_::Vector_2             Vector_2;
  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Direction_2          Direction_2;

// TODO : we have 2 levels of ref-counting here.
  typedef Vector_2                          Rep;
  typedef typename R_::template Handle<Rep>::type  Base;

  typedef Rational_traits<FT>  Rat_traits;

  Base base;

public:

  typedef FT Cartesian_coordinate_type;
  typedef const RT& Homogeneous_coordinate_type;
  typedef typename Rep::Cartesian_const_iterator Cartesian_const_iterator;
  typedef R_                                    R;

    PointH2() {}

    PointH2(const Origin &)
      : base(NULL_VECTOR) {}

    template < typename Tx, typename Ty >
    PointH2(const Tx & x, const Ty & y,
            typename boost::enable_if< boost::mpl::and_<boost::is_convertible<Tx, RT>,
                                                        boost::is_convertible<Ty, RT> > >::type* = 0)
      : base(x, y) {}

    PointH2(const FT& x, const FT& y)
      : base(x, y) {}

    PointH2(const RT& hx, const RT& hy, const RT& hw)
      : base(hx, hy, hw) {}

    bool    operator==( const PointH2<R>& p) const;
    bool    operator!=( const PointH2<R>& p) const;

    const RT & hx() const { return get(base).hx(); }
    const RT & hy() const { return get(base).hy(); }
    const RT & hw() const { return get(base).hw(); }

    FT      x()  const { return FT(hx()) / FT(hw()); }
    FT      y()  const { return FT(hy()) / FT(hw()); }

    FT      cartesian(int i)   const;
    FT      operator[](int i)  const;
    const RT & homogeneous(int i) const;

    Cartesian_const_iterator cartesian_begin() const
    {
      return get(base).cartesian_begin();
    }

    Cartesian_const_iterator cartesian_end() const
    {
      return get(base).cartesian_end();
    }

    int     dimension() const;

    Direction_2 direction() const;
};

template < class R >
CGAL_KERNEL_INLINE
bool
PointH2<R>::operator==( const PointH2<R>& p) const
{
  return get(base) == get(p.base);
}

template < class R >
inline
bool
PointH2<R>::operator!=( const PointH2<R>& p) const
{ return !(*this == p); }

template < class R >
CGAL_KERNEL_INLINE
typename PointH2<R>::FT
PointH2<R>::cartesian(int i) const
{
  return get(base).cartesian(i);
}

template < class R >
CGAL_KERNEL_INLINE
const typename PointH2<R>::RT &
PointH2<R>::homogeneous(int i) const
{
  return get(base).homogeneous(i);
}

template < class R >
inline
typename PointH2<R>::FT
PointH2<R>::operator[](int i) const
{ return get(base)[i]; }


template < class R >
inline
int
PointH2<R>::dimension() const
{ return get(base).dimension(); }

template < class R >
CGAL_KERNEL_INLINE
typename PointH2<R>::Direction_2
PointH2<R>::direction() const
{ return typename PointH2<R>::Direction_2(*this); }

CGAL_END_NAMESPACE

#endif // CGAL_HOMOGENEOUS_POINT_2_H
