#include <cmath>

#include "3d_ext.h"

double toRad(double angle) {
	return (3.14159265359 / 180) * angle;
}

double toAngle(double rad) {
	return (180 / 3.14159265359) * rad;
}

Vector::Vector(double x0, double y0, double z0) {
	x = x0; y = y0; z = z0;
}
Vector Vector::operator*(double a) {
	return Vector(x * a, y * a, z * a);
}
Vector Vector::operator/(double a) { 
	return Vector(x / a, y / a, z / a);
}
Vector Vector::operator+(const Vector& v) {
 	return Vector(x + v.x, y + v.y, z + v.z);
}
Vector Vector::operator-(const Vector& v) {
 	return Vector(x - v.x, y - v.y, z - v.z);
}
double Vector::operator*(const Vector& v) { //dot product
	return (x * v.x + y * v.y + z * v.z);
}
Vector Vector::operator%(const Vector& v) { //cross product
	return Vector(y*v.z-z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}
double Vector::Length() {
	return sqrt(x * x + y * y + z * z);
}

bool sameSide(Vector p1, Vector p2, Vector a, Vector b) { //returns with true if p1 and p2 are on the same side of the line AB
	 Vector cp1 = (b-a) % (p1-a);
	 Vector cp2 = (b-a) % (p2-a);
	 if ((cp1 * cp2) >= 0)
		return true;
	 else
		return false;
}


Color::Color(double r0, double g0, double b0) { 
	r = r0; g = g0; b = b0;
}
Color Color::operator*(double a) { 
	return Color(r * a, g * a, b * a); 
}
Color Color::operator*(const Color& c) { 
	return Color(r * c.r, g * c.g, b * c.b); 
}
Color Color::operator+(const Color& c) {
	return Color(r + c.r, g + c.g, b + c.b); 
}
Color Color::operator/(const float x) {
	return Color(r / x, g / x, b / x); 
}

Color c_red(1, 0, 0);
Color c_green(0, 1, 0);
Color c_blue(0, 0, 1);
Color c_yellow(1, 1, 0);
Color c_magenta(1, 0, 1);
Color c_cyan(0, 1, 1);
Color c_white(1, 1, 1);
Color c_black(0, 0, 0);
