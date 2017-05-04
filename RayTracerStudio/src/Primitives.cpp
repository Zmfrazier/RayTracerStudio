#include "Primitives.hpp"

Point 
operator + (const Point& p, const Vector& v){
	Point p2 = {p.x + v.x, p.y + v.y, p.z + v.z };
	return p2;
}

Point 
operator - (const Point& p, const Vector& v){
	Point p2 = {p.x - v.x, p.y - v.y, p.z - v.z };
	return p2;
}

Vector 
operator + (const Vector& v1, const Vector& v2){
	Vector v = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	return v;
}

Vector 
operator - (const Point& p1, const Point& p2){
	Vector v = {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };
	return v;
}

Vector 
operator * (float c, const Vector& v)
{
	Vector v2 = {v.x * c, v.y * c, v.z * c};
	return v2;
}

Vector 
operator - (const Vector& v1, const Vector& v2){
	Vector v={v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	return v;
}

float 
operator * (const Vector& v1, const Vector& v2 ) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector 
operator ^ (const Vector& v1, const Vector& v2) {
    Vector v = {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
    return v;
}

Color 
operator * (const Color& c1, const Color& c2 ) {
	Color c = {c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue};
	return c;
}

Color 
operator + (const Color&c1, const Color &c2 ) {
	Color c = {c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue};
	return c;
}

Color 
operator * (float coef, const Color &c ) {
	Color c2 = {c.red * coef, c.green * coef, c.blue * coef};
	return c2;
}