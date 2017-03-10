#include <math.h>
#include "Vector.hpp"

double
Vector::length() const {
  return sqrt(x*x + y*y + z*z);
}

Vector
Vector::normalize(){
  return (*this) /= this->length();
}

Vector
Vector::cross(const Vector& v) const {
  return Vector((y*v.z) - (v.y*z), (v.x*z) - (x*v.z), (x*v.y) - (v.x*y));
}

double
Vector::dot(const Vector& v) const {
  return (x*v.x) + (y*v.y) + (z*v.z);
}

Vector
Vector::operator + (const Vector& vector) const{
  return Vector(x + vector.x, y + vector.y, z + vector.z);
}

Vector
Vector::operator - (const Vector& vector) const{
  return Vector(x - vector.x, y - vector.y, z - vector.z);
}

Vector
Vector::operator * (const Vector& vector) const{
  return Vector(x * vector.x, y * vector.y, z * vector.z);
}

Vector
Vector::operator / (const Vector& vector) const{
  return Vector(x / vector.x, y / vector.y, z / vector.z);
}

Vector&
Vector::operator += (const Vector& vector){
  x += vector.x;
  y += vector.y;
  z += vector.z;

  return *this;
}

Vector&
Vector::operator -= (const Vector& vector){
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;

  return *this;
}

Vector&
Vector::operator *= (const Vector& vector){
  x *= vector.x;
  y *= vector.y;
  z *= vector.z;

  return *this;
}

Vector&
Vector::operator /= (const Vector& vector){
  x /= vector.x;
  y /= vector.y;
  z /= vector.z;

  return *this;
}

