#ifndef __COLOR_HPP__
#define __COLOR_HPP__

class Color {
public:
  double r, g, b, a;

  Color() : r(0.0), g(0.0), b(0.0), a(1.0) {}
  Color(double red, double green, double blue) : r(red), g(green), b(blue), a(1.0) {}
  Color(double red, double green, double blue, double alpha) : r(red), g(green), b(blue), a(alpha) {}
};

#endif