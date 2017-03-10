#ifndef __RAY_HPP__
#define __RAY_HPP__

#include <stdlib.h>
#include "Vector.hpp"

class Material;

class Ray {
public:
   Vector origin;
   Vector direction;
   int reflectionsLeft;
};

#endif