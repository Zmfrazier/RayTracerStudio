#ifndef __Primitives_H
#define __Primitives_H

//a Point with three float numbers indicating its location in 3d world
struct Point {
	float x, y, z;
};

//Color structure with three float numbers indicating values
struct Color {
    float red, green, blue;
};

//a 3d vector with three float numbers indicating its values in three dimentions
struct Vector {
	float x, y, z;
};

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
operator * (float coef, const Color& c );

#endif 
