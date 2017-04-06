#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <math.h>
#include "Vector.hpp"
#include "Intersection.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Boundaries.hpp"

class Sphere : public Object {
   public:
      Vector center;
      double radius;
      Boundaries bounds;

      virtual Intersection intersect(Ray);
      virtual Boundaries getBounds();

private:
   Color getColor(Vector);
};

#endif