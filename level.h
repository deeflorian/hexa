#ifndef _LEVEL
#define _LEVEL

#include "3d_ext.h"
#include "blocklist.h"

class Level {
	//draws an isosceles triangle with the passed mid-angle
	void draw_triangle(double angle);
	void draw_strip(double angle);
	inline double line_solver(double x);
	void draw_block_quad(double strip, double d);

	//draw an n-gon with an extra side of an angle of bonus
	void draw_ngon(int n, Color A, Color B, double bonus = 0.0);
	void draw_nstrip(int n, Color A, Color B, double bonus = 0.0);
	void draw_player();

	
	void draw_block(Block& b);
public:
	BlockList* blocks;
	bool strip_block[10];
	Color c_hexagon;
	Color c_hexagon_inside;
	Color c_strip[2];
	Color c_player;
	bool playing;
	double extra_angle;
	double player_angle;
	int n_sides;
	double triangle_a;
	double triangle_m;
	double triangle_top;
	double strip_rate; //relative size of a strip compared to a triangle
	double getHeight();
	void setExtraAngle(double an);
	void setSides(int i);
	Level(BlockList* b, double hexagonWidth = 2.0, double levelHeight = 5, double levelSideRate = 200.0);
	void draw();
};

#endif
