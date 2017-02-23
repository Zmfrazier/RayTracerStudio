#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Vector.hpp"

class Camera {
public:
  Vector position;
  Vector w, u, v;
  Vector up;
  Vector pointedAt;
  double screenWidth;

  Camera() {
    position = Vector(0.0, 0.0, 100.0);
    up = Vector(0.0, 1.0, 0.0);
    lookAt = Vector(0.0, 0.0, 0.0);
    screenWidth = 1000;

    calculateWUV();
  }

  Camera(
    Vector p, 
    Vector u,
    Vector l, 
    double s
    ) 
    :
    position(p), 
    up(u), 
    lookAt(l), 
    screenWidth(s) 
    {calculateWUV();}

  void calculateWUV();
};

#endif