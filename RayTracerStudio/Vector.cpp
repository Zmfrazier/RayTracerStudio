#include <math.h>
#include "Vector.hpp"

Vector
Vector::length(){
  return sqrt(x*x + y*y + z*z);
}

Vector
Vector::normalize(){
  return (*this) /= this->length();
}

Vector
Vector::cross(Vector const & v) const {
  return Vector((y*v.z) - (v.y*z), (v.x*z) - (x*v.z), (x*v.y) - (v.x*y));
}

double
Vector::dot(Vector const & v) const {
  return (x*v.x) + (y*v.y) + (z*v.z);
}

Vector
Vector::operator + (Vector const & vector) const{
  return vector(x + vector.x, y + vector.y, z + vector.z)
}

Vector
Vector::operator - (Vector const & vector) const{
  return vector(x - vector.x, y - vector.y, z - vector.z)
}

Vector
Vector::operator * (Vector const & vector) const{
  return vector(x * vector.x, y * vector.y, z * vector.z)
}

Vector
Vector::operator / (Vector const & vector) const{
  return vector(x / vector.x, y / vector.y, z / vector.z)
}

Vector
Vector::operator += (Vector const & vector){
  x += vector.x;
  y += vector.y;
  z += vector.z;

  return *this;
}

Vector
Vector::operator -= (Vector const & vector){
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;

  return *this;
}

Vector
Vector::operator *= (Vector const & vector){
  x *= vector.x;
  y *= vector.y;
  z *= vector.z;

  return *this;
}

Vector
Vector::operator /= (Vector const & vector){
  x /= vector.x;
  y /= vector.y;
  z /= vector.z;

  return *this;
}

