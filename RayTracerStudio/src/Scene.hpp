#ifndef __SCENE_H
#define __SCENE_H
#include <vector>

struct Camera{
	float Horizontal;
	float Vertical;
	float Depth;
	vector3d rotate;
};

struct Scene {
    std::vector<Material> MaterialContainer;
    std::vector<Sphere>   SphereContainer;
    std::vector<Plane>    PlaneContainer;
	std::vector<Light>    LightContainer;
    std::vector<Triangle> TriangleContainer;
    std::vector<Disc>	  DiscContainer;

    int Size_X, Size_Y;

    Camera Cam;
};

bool initialize(char* InputName, Scene &MyScene);

#endif
