#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include <limits>
#include "Vector.h"
#include "Object.h"
#include "Color.h"
#include "Ray.h"

class Intersection {
public:
   Ray ray;
   bool didIntersect;
   Vector normal;
   Object* object;
   Vector intersection;
   double distance;


   Color getColor() const {
   return endMaterial->getColor(intersection);
  }
};

#endif