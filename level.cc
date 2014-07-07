#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "3d_ext.h"
#include "blocklist.h"
#include "level.h"

void Level::draw_triangle(double angle) {
	double radian = toRad(angle);
	glBegin(GL_TRIANGLES);
		glVertex3d(0, triangle_top, 0);
		glVertex3d(triangle_a, triangle_top, 0);
		glVertex3d(triangle_a * cos(radian), triangle_top, triangle_a * sin(radian));
	glEnd();
}

void Level::draw_strip(double angle) {
	double radian = toRad(angle);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3d(triangle_a, triangle_top, 0);
		glVertex3d(triangle_a * strip_rate, 0, 0);
		glVertex3d(triangle_a * cos(radian), triangle_top, triangle_a * sin(radian));
		glVertex3d(triangle_a * cos(radian) * strip_rate, 0, triangle_a * sin(radian) * strip_rate);
	glEnd();
}

inline double Level::line_solver(double x) {
	return (triangle_top*triangle_a - triangle_top*x) / (triangle_a * strip_rate - triangle_a) + triangle_top;
}

void Level::draw_block_quad(double strip, double d) {
	double one_rotation = (360.0 - extra_angle) / n_sides;
	double radian = (strip!=n_sides) ? toRad(one_rotation) : toRad(extra_angle);
	double d2 = d + triangle_a;
	glPushMatrix();
	glRotatef(-one_rotation * strip, 0, 1, 0);
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3d(d, line_solver(d), 0);
			glVertex3d(d2, line_solver(d2), 0);
			glVertex3d(d * cos(radian), line_solver(d), d * sin(radian));
			glVertex3d(d2 * cos(radian), line_solver(d2), d2 * sin(radian));
		glEnd();
	glPopMatrix();
}

//draw an n-gon with an extra side of an angle of bonus
void Level::draw_ngon(int n, Color A, Color B, double bonus) {
	double one_rotation = (360.0 - bonus) / n;
	Color interpol((A+B)/2);

	glPushMatrix();
		for(int i = 0; i < n; ++i) {
			if((i == (n-1))  &&  ((i%2) != 1) && bonus == 0) {
				glColor3f(interpol.r, interpol.g, interpol.b); //if n-gon has an odd number of sides, interpolate colors
			}
			else {
				if((i%2) == 0) {
					glColor3f(A.r, A.g, A.b);
					if((n%2) == 1 && (i == (n-1)) && bonus >= 0) { //if n-gon has an odd num. of sides with a bonus side
						double interpolness = (360.0/(n+1));	   //draw the last complete side with an interpol. color
						Color hm = interpol * (1 - bonus/interpolness) + A * bonus / interpolness;
						glColor3f(hm.r, hm.g, hm.b);
					}
				}
				else {
					glColor3f(B.r, B.g, B.b);
				}
			}
			draw_triangle(one_rotation);
			glRotatef(-one_rotation, 0, 1, 0);
		}
		if(bonus > 0) {
			if((n%2) == 0) {
				glColor3f(interpol.r, interpol.g, interpol.b); //if n-gon has an odd number of sides, interpolate colors
			}
			else
				glColor3f(B.r, B.g, B.b);
			draw_triangle(bonus);
		}
	glPopMatrix();
}

void Level::draw_nstrip(int n, Color A, Color B, double bonus) {
	double one_rotation;
	Color interpol((A+B)/2);
	if(bonus > 0) {
		one_rotation = (360.0 - bonus) / n;
	}
	else {
		one_rotation = 360.0 / n;
	}

	glPushMatrix();
		for(int i = 0; i < n; ++i) {
			if((i == (n-1))  &&  ((i%2) != 1) && bonus == 0) {
				glColor3f(interpol.r, interpol.g, interpol.b); //if n-gon has an odd number of sides, interpolate colors
			}
			else {
				if((i%2) == 0) {
					glColor3f(A.r, A.g, A.b);
					if((n%2) == 1 && (i == (n-1)) && bonus >= 0) {
						double interpolness = (360.0/(n+1));
						Color hm = interpol * (1 - bonus/interpolness) + A * bonus / interpolness;
						glColor3f(hm.r, hm.g, hm.b);
					}
				}
				else {
					glColor3f(B.r, B.g, B.b);
				}
			}
			draw_strip(one_rotation);
			glRotatef(-one_rotation, 0, 1, 0);
		}
		if(bonus > 0) {
			if((n%2) == 0) {
				glColor3f(interpol.r, interpol.g, interpol.b); //if n-gon has an odd number of sides, interpolate colors
			}
			else
				glColor3f(B.r, B.g, B.b);
			draw_strip(bonus);
		}
	glPopMatrix();
}

void Level::draw_player() {
	glPushMatrix();
		glRotatef(-player_angle, 0, 1, 0);
		float rate = 2;
		glColor3f(c_player.r*0.3, c_player.g*0.3, c_player.b*0.3);
		glPushMatrix();
			glScalef(1.03, 1.03, 1.03);
			glBegin(GL_TRIANGLES);
				glVertex3d(triangle_a + triangle_a*0.2*rate, triangle_top - triangle_top*0.02, 0);
				glVertex3d(triangle_a + triangle_a*0.05*rate, triangle_top - triangle_top*0.02, triangle_a*0.08*rate);
				glVertex3d(triangle_a + triangle_a*0.05*rate, triangle_top - triangle_top*0.02, -triangle_a*0.08*rate);
			glEnd();
		glPopMatrix();

		glColor3f(c_player.r, c_player.g, c_player.b);
		glBegin(GL_TRIANGLES);
			glVertex3d(triangle_a + triangle_a*0.2*rate, triangle_top, 0);
			glVertex3d(triangle_a + triangle_a*0.05*rate, triangle_top, triangle_a*0.08*rate);
			glVertex3d(triangle_a + triangle_a*0.05*rate, triangle_top, -triangle_a*0.08*rate);
		glEnd();
	glPopMatrix();
}

	
void Level::draw_block(Block& b) {
	//dont draw if block is from a bigger n_gon formation
	if(b.strip > n_sides || (b.strip == n_sides && extra_angle == 0) || b.d_block > triangle_a * strip_rate) return;

	int player_strip;
	while(player_angle < 0) player_angle += 360;
	while(player_angle > 360) player_angle -= 360;
	if(extra_angle != 0 && player_angle > (360-extra_angle)) {
		player_strip = n_sides;
	}
	else {
		player_strip = player_angle / ((360-extra_angle) / n_sides);
	}

	if((triangle_a * 1.2 > b.d_block) && player_strip == b.strip) {
		playing = false;
	}

	//draw
	Color c = c_hexagon * (3+b.c_offset) / 4;
	glColor3f(c.r, c.g, c.b);
	draw_block_quad(b.strip, b.d_block);
}

double Level::getHeight() {
	return triangle_top;
}

void Level::setExtraAngle(double an) {
	if(an > 0)
		extra_angle = an;
	else
		extra_angle = 0;
}

void Level::setSides(int i) {
	n_sides = i;
}

Level::Level(BlockList* b, double hexagonWidth, double levelHeight, double levelSideRate) {
	c_player = c_red;
	c_hexagon = c_red*0.9;
	c_hexagon_inside = c_red*0.45;
	c_strip[0] = c_red*0.6;
	c_strip[1] = c_red * 0.3;


	blocks = b;
	playing = true;
	for(int i = 10; i < 50; i+=5) {
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
	}
	for(int i = 50; i < 80; i+=5)
	{
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
	}
	BlockTypeS(*blocks, 80, 10);
	for(int i = 110; i < 1000; i+=5) {
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
		BlockTypeB(*blocks, i, 10);
	}

	for(int i = 0; i < 10; ++i) strip_block[i] = false;
	triangle_a = hexagonWidth / 2;
	triangle_m = sin(3.14159265359/3) * triangle_a;
	triangle_top = levelHeight;
	strip_rate = levelSideRate;
	extra_angle = 0;
	n_sides = 6;
	player_angle = 0;
}

void Level::draw() {
	//Playfield
	draw_nstrip(n_sides, c_strip[0], c_strip[1], extra_angle);

	for(int i = 0; i < 10; ++i) strip_block[i] = false;

	for(std::list<Block>::iterator i = (*blocks).blocks.begin(); i != (*blocks).blocks.end(); ++i) {
		draw_block((*i));
		if((triangle_a * 1.2 > ((*i).d_block))) {
			strip_block[((*i).strip)] = true;
		}
	}

	draw_ngon(n_sides, c_hexagon, c_hexagon, extra_angle);

	glPushMatrix();
		glScalef(0.95, 1.00, 0.95);
		draw_ngon(n_sides, c_hexagon_inside, c_hexagon_inside, extra_angle);
	glPopMatrix();

	draw_player();
}
