#ifndef __RAY_TRACER_H__
#define __RAY_TRACER_H__

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include "Vector.h"
#include "Camera.h"

class Ray;
class Color;
class Intersection;
class Object;
class Light;

class RayTracer {
public:
   int width;
   int height;
   int maxReflections;
   int superSamples; // Square root of number of samples to use for each pixel.
   Camera camera;
   double imageScaling;
   int depthComplexity;
   unsigned long long raysCast;
   BSP* bsp;

   std::vector<Object*> objects;
   std::vector<Light*> lights;
   std::map<std::string, Material*> materials;

   RayTracer(int, int, int, int, int);

   ~RayTracer();

   void addObject(Object* object) {
      objects.push_back(object);
   }

   void addLight(Light* light) {
      lights.push_back(light);
   }

   void traceRays(std::string);

private:
   Color castRayForPixel(int, int);
   Color castRayAtPoint(const Vector&);
};

#endif