// Copyright (c) 2000  Utrecht University (The Netherlands),
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
// Author(s)     : Andreas Fabri and Herve Bronnimann

#ifndef CGAL_CARTESIAN_POINT_3_H
#define CGAL_CARTESIAN_POINT_3_H

#include <CGAL/Handle_for.h>
#include <CGAL/Origin.h>
#include <CGAL/constant.h>

CGAL_BEGIN_NAMESPACE

template < class R_ >
class PointC3
{
  typedef typename R_::FT                   FT;
  typedef typename R_::Vector_3             Vector_3;
  typedef typename R_::Point_3              Point_3;
  typedef typename R_::Aff_transformation_3 Aff_transformation_3;

// TODO : we have 2 levels of ref-counting here.
  typedef Vector_3                          Rep;
  typedef typename R_::template Handle<Rep>::type  Base;

  Base base;

public:
  typedef typename Rep::Cartesian_const_iterator Cartesian_const_iterator;
  typedef R_                                R;

  PointC3() {}

  PointC3(const Origin &)
    : base(NULL_VECTOR) {}

  PointC3(const FT &x, const FT &y, const FT &z)
    : base(x, y, z) {}

  PointC3(const FT &x, const FT &y, const FT &z, const FT &w)
    : base(x, y, z, w) {}

  const FT & x() const
  {
      return get(base).x();
  }
  const FT & y() const
  {
      return get(base).y();
  }
  const FT & z() const
  {
      return get(base).z();
  }

  const FT & hx() const
  {
      return x();
  }
  const FT & hy() const
  {
      return y();
  }
  const FT & hz() const
  {
      return z();
  }
  const FT & hw() const
  {
      return constant<FT, 1>();
  }

  const FT & cartesian(int i) const;
  const FT & operator[](int i) const;
  const FT & homogeneous(int i) const;

  Cartesian_const_iterator cartesian_begin() const 
  {
    return get(base).cartesian_begin(); 
  }

  Cartesian_const_iterator cartesian_end() const 
  {
    return get(base).cartesian_end();
  }

  int dimension() const
  {
      return get(base).dimension();
  }

  Point_3 transform(const Aff_transformation_3 &t) const
  {
    return t.transform(*this);
  }
};

template < class R >
inline
const typename PointC3<R>::FT &
PointC3<R>::cartesian(int i) const
{
  return get(base).cartesian(i);
}

template < class R >
inline
const typename PointC3<R>::FT &
PointC3<R>::operator[](int i) const
{
  return get(base)[i];
}

template < class R >
inline
const typename PointC3<R>::FT &
PointC3<R>::homogeneous(int i) const
{
  return get(base).homogeneous(i);
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_POINT_3_H
