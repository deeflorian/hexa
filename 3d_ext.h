#ifndef _3D_EXT
#define _3D_EXT

double toRad(double angle);

double toAngle(double rad);

class Vector {
public:
	double x, y, z;
	Vector(double x0 = 0, double y0 = 0, double z0 = 0);
	Vector operator*(double);
	Vector operator/(double);
	Vector operator+(const Vector&);
	Vector operator-(const Vector&);
	double operator*(const Vector&);
	Vector operator%(const Vector&);
	double Length();
};

class Color {
public:
   double r, g, b;
   Color(double r0 = 0, double g0 = 0, double b0 = 0);
   Color operator*(double a);
   Color operator*(const Color& c);
   Color operator+(const Color& c);
   Color operator/(const float x);
};

bool sameSide(Vector p1, Vector p2, Vector a, Vector b); //returns with true if p1 and p2 are on the same side of the line AB

extern Color c_red;
extern Color c_green;
extern Color c_blue;
extern Color c_yellow;
extern Color c_magenta;
extern Color c_cyan;
extern Color c_white;
extern Color c_black;


#endif
