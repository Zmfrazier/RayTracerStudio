#ifndef __RAY_TRACER_HPP__
#define __RAY_TRACER_HPP__
#include <vector>

class Object;
class Light;

class RayTracer{
public:
  int width;
  int height;
  int maxReflections;
  
  Camera camera;

  std::vector<Object*> objects;
  std::vector<Light*> lights;

  void
  addObject(Object*);

  void
  addLight(Light*);

  RayTracer();
  ~RayTracer();

};

#endif