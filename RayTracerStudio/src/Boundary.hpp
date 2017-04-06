#ifndef __BOUNDARY_H__
#define __BOUNDARY_H__

#include "Vector.h"
#include "Ray.h"

class Boundaries {
public:
   Vector minimum, maximum;

   Boundaries() : minimum(Vector(0, 0, 0)), maximum(Vector(0, 0, 0)) {}

   bool intersect(const Ray&, double* dist);
};

#endif