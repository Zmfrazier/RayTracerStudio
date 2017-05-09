#include "Primitives.hpp"

Point 
operator + (const Point& p, const Vector& v){
    Point pt = {p.x + v.x, p.y + v.y, p.z + v.z };
    return pt;
}

Point 
operator - (const Point& p, const Vector& v){
    Point pt = {p.x - v.x, p.y - v.y, p.z - v.z };
    return pt;
}

Vector 
operator + (const Vector& v1, const Vector& v2){
    Vector vec = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return vec;
}

Vector 
operator - (const Point& p1, const Point& p2){
    Vector v = {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };
    return v;
}

Vector 
operator * (float c, const Vector& v)
{
    Vector vec = {v.x * c, v.y * c, v.z * c};
    return vec;
}

Vector 
operator - (const Vector& v1, const Vector& v2){
    Vector vec = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return vec;
}

float 
operator * (const Vector& v1, const Vector& v2 ) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector 
operator ^ (const Vector& v1, const Vector& v2) {
    Vector vec = {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
    return vec;
}

Color 
operator * (const Color& c1, const Color& c2) {
    Color c = {c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue};
    return c;
}

Color 
operator + (const Color&c1, const Color &c2) {
    Color c = {c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue};
    return c;
}

Color 
operator * (float coefficient, const Color &c) {
    Color c2 = {c.red * coefficient, c.green * coefficient, c.blue * coefficient};
    return c2;
}