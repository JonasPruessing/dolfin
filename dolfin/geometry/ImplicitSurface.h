// Copyright (C) 2013 Garth N. Wells
//
// This file is part of DOLFIN.
//
// DOLFIN is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DOLFIN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with DOLFIN. If not, see <http://www.gnu.org/licenses/>.
//
// First added:  2013-05-04
// Last changed:

#ifndef __IMPLICITSURFACE_H
#define __IMPLICITSURFACE_H

#include <string>
#include <utility>
#include <vector>
#include <dolfin/generation/CSGPrimitives3D.h>
#include <dolfin/geometry/Point.h>
#include <dolfin/log/log.h>

namespace dolfin
{

  /// This class is used to define a surface via a function f(x) -> R,
  /// where for a point y on the surface f(y) = 0.

  class ImplicitSurface
  {
  public:

    /// Create an isosurface
    ///
    /// *Arguments*
    ///     s (Sphere)
    ///         Bounding sphere for surface.
    ///
    ///     type (std::string)
    ///         Isosurface type. One of "manifold", "manifold_with_boundary"
    ///         or "non_manifold".
    ///
    /// *Example*
    ///     .. code-block:: c++
    ///
    ///         IsoSurface isosurface(Sphere(Point(0.0, 0.2, 0.4), 1.0),
    ///                               "manifold_with_boundary");
    ///
    ImplicitSurface(Sphere s, std::string type);

    /// Destructor
    virtual ~ImplicitSurface();

    /// Return value of isosurfacce function. This function is
    /// overloaed by the user. For closed volumes, the function should
    /// evaluate to < 0 on the interior.
    ///
    /// *Arguments*
    ///     point (Point)
    ///         The point at which to evaluate the isosurface function.
    ///         or "non_manifold".
    ///
    /// *Returns*
    ///     double
    ///         Isosurface function value.
    virtual double operator()(const Point& point) const = 0;

    virtual double signed_distance(const Point& point) const
    {
      error("ImplicitSurface::signed_distance has not been provided");
      return 0.0;
    }

    /// Test whether a point for which f \approx 0 is on the
    /// surface. Used for creating open surfaces by discarding with
    /// any artificial closure.
    virtual bool on_surface(const Point& point) const
    { return true; }

    /// Bounding sphere
    const Sphere sphere;

    /// Polylines
    std::vector<std::pair<Point, Point> > polylines;

    /// Surface type
    const std::string type;

  };

}

#endif
