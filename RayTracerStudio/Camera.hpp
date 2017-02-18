#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Vector.hpp"

class Camera {
public:
   Vector position;

   Camera() {
      position = Vector(0.0, 0.0, 100.0);
   }
};

#endif