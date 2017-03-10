#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

class Vector{

public:
  double x, y, z;

  Vector() : x(0), y(0), z(0) {}

  Vector(double n) : x(n), y(n), z(n) {}

  Vector(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

  double
  length() const;

  Vector
  normalize();

  Vector
  cross(Vector const & v) const;

  double
  dot(Vector const & v) const;

  Vector
  operator + (Vector const & v) const;

  Vector
  operator - (Vector const & v) const;

  Vector
  operator * (Vector const & v) const;

  Vector
  operator / (Vector const & v) const;

  Vector&
  operator += (Vector const & v);

  Vector&
  operator -= (Vector const & v);

  Vector&
  operator *= (Vector const & v);

  Vector&
  operator /= (Vector const & v);
};

#endif