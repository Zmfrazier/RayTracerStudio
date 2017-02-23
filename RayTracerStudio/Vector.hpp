#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

class Vector{

public:
  double x, y, z;

  Vector()
  : x(0), y(0), z(0) {}

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