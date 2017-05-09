#ifndef __PRIMITIVES_HPP
#define __PRIMITIVES_HPP
#include <vector>

struct Point {
	float x, y, z;
};

struct Color {
    float red, green, blue;
};

struct Vector {
	float x, y, z;
};

struct Material {
    float reflection;
	float red, green, blue;
	float power;
	float specular;
};

struct Sphere {
	Point pos;
	float size;
	int materialId;
};

struct Plane {
    Point pos;
    Vector normal;
    int materialId;
};

struct Light {
	Point pos;
	Color intensity;
};

struct Ray {
	Point start;
	Vector dir;
};

struct Camera{
    float Horizontal;
    float Vertical;
    float Depth;
    Vector Rotate;
};

struct Scene {
    std::vector<Material> Materials;
    std::vector<Sphere>   Spheres;
    std::vector<Plane>    Planes;
    std::vector<Light>    Lights;

    int width, height;

    Camera Cam;
};

bool Initialize(char* InputName, Scene &MyScene);

#define invsqrtf(x) ((1.0f) / sqrtf(x))

Point 
operator + (const Point& p, const Vector& v);

Point 
operator - (const Point& p, const Vector& v);

Vector 
operator + (const Vector& v1, const Vector& v2);

Vector 
operator - (const Point& p1, const Point& p2);

Vector 
operator * (float c, const Vector& v);

Vector 
operator - (const Vector& v1, const Vector& v2);

float 
operator * (const Vector& v1, const Vector& v2 );

Vector 
operator ^ (const Vector& v1, const Vector& v2);

Color 
operator * (const Color& c1, const Color& c2 );

Color 
operator + (const Color& c1, const Color& c2 );

Color 
operator * (float coefficient, const Color& c );

#endif 
