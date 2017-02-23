#include "RayTracer.hpp"

void
RayTracer::addObject(Object* object){
  objects.push_back(object);
}

void
RayTracer::addLight(*Light light){
  lights.push_back(light);
}