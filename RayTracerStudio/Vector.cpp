#include "Vector.hpp"

Vector Vector::cross(Vector const & v) const {
  return Vector( (y*v.z) - (v.y*z), (v.x*z) - (x*v.z), (x*v.y) - (v.x*y) );
}

double Vector::dot(Vector const & v) const {
  return (x*v.x) + (y*v.y) + (z*v.z);
}

