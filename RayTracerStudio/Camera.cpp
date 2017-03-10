#include "Camera.hpp"

void
Camera::calculateWUV(){
  w = (pointedAt - position).normalize();
  u = up.cross(w).normalize();
  v = w.cross(u);
}