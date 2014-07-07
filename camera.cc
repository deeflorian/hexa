#include <cmath>

#include "3d_ext.h"
#include "camera.h"

Camera::Camera(double R, double H) {
	position = Vector(0, H, R);
	h = H;
	r = R;
	hx = r * r / h;
	at = Vector(0, 0, 0);
	up = Vector(0, h + hx, 0) - position;
}

void Camera::rotate(double angle) { //rotates the camera around the y axis
	double x, z;
	double radAngle = toRad(angle);
	x = position.x * cos(radAngle) - position.z * sin(radAngle);
	z = position.x * sin(radAngle) + position.z * cos(radAngle);
	position = Vector(x, position.y, z);
	up = Vector(0, h + hx, 0) - position;
}

void Camera::distance(double len) { //set camera distance from the y axis
	double b = len * position.z / r;
	double a = len * position.x / r;
	r = len;
	hx = r * r / h;
	position = Vector(a, position.y, b);
	up = Vector(0, h + hx, 0) - position;
}

void Camera::height(double he) { //set camera height above the x-z plane
	position = position * (he/h);
	r = sqrt(position.x*position.x + position.z*position.z);
	h = he;
	hx = r * r / h;
	up = Vector(0, h + hx, 0) - position;
}
