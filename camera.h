#ifndef _CAMERA_H
#define _CAMERA_H

#include "3d_ext.h"

struct Camera {
	Vector position, at, up;
	double r, h, hx;
	Camera(double R = 1.0, double H = 10.0);
	void rotate(double angle);
	void distance(double len);
	void height(double he);
};

#endif
