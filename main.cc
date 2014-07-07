#include <iostream>
#include <list>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "3d_ext.h"
#include "camera.h"
#include "blocklist.h"
#include "shifter.hpp"
#include "level.h"

int screenWidth = 1366;
int screenHeight = 768;

double angle_per_msec = 0.5;
double distance_per_msec = 0.006;

BlockList blocklist(distance_per_msec);

shiftreg SHR;

long c_time, p_time, d_time; //current, previous, and delta time
Level level(&blocklist);
Camera camera;

void onDisplay( ) {
	p_time = c_time;
	c_time = glutGet(GLUT_ELAPSED_TIME);
	d_time = c_time - p_time;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, ((float)screenWidth)/screenHeight, 0.0001, 100.0);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	Vector position, at, up;
	gluLookAt(camera.position.x, camera.position.y, camera.position.z,
				0, level.getHeight(), 0,
				camera.up.x, camera.up.y, camera.up.z);

	level.draw();

	glutSwapBuffers();
}

void drawMenu() {
}

bool key_a_pressed, key_d_pressed;
long key_a_start, key_d_start;
void onKeyboard(unsigned char key, int x, int y) {
	if(key == 'i') camera.distance(camera.r + 0.2);
	if(key == 'k') camera.distance(camera.r - 0.2);
	if(key == ' ') camera.height(camera.h + 0.2);
	if(key == 'c') camera.height(camera.h - 0.2);

	if(key == 'a') {
		key_a_pressed = true;
		key_a_start = glutGet(GLUT_ELAPSED_TIME);
	}
	if(key == 'd') {
		key_d_pressed = true;
		key_d_start = glutGet(GLUT_ELAPSED_TIME);
	}
	onDisplay();
}

void onKeyboardUp(unsigned char key, int x, int y) {
	if(key == 'a') {
		key_a_pressed = false;
	}
	if(key == 'd') {
		key_d_pressed = false;
	}
}

void movePlayer() {
		if(!level.playing) return;
		int player_strip;

		long key_now, key_elapsed;
		key_now = glutGet(GLUT_ELAPSED_TIME);
		if(key_a_pressed) {
			key_elapsed = key_now - key_a_start;
			key_a_start = key_now;
			double new_angle = level.player_angle - angle_per_msec * key_elapsed;

			while(new_angle < 0) new_angle += 360;
			while(new_angle > 360) new_angle -= 360;
			if(level.extra_angle != 0 && new_angle > (360-level.extra_angle)) {
				player_strip = level.n_sides;
			}
			else {
				player_strip = new_angle / ((360-level.extra_angle) / level.n_sides);
			}

			if (level.strip_block[player_strip]) {
				
			}
			else
			level.player_angle -= angle_per_msec * key_elapsed;
		}
		if(key_d_pressed) {
			key_elapsed = key_now - key_d_start;
			key_d_start = key_now;
			double new_angle = level.player_angle + angle_per_msec * key_elapsed;

			while(new_angle < 0) new_angle += 360;
			while(new_angle > 360) new_angle -= 360;
			if(level.extra_angle != 0 && new_angle > (360-level.extra_angle)) {
				player_strip = level.n_sides;
			}
			else {
				player_strip = new_angle / ((360-level.extra_angle) / level.n_sides);
			}

			if (level.strip_block[player_strip]) {
				
			}
			else
			level.player_angle += angle_per_msec * key_elapsed;
		}
}

void onMouse(int button, int state, int X, int Y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		level.n_sides++;
		std::cout << glutGet(GLUT_ELAPSED_TIME) << std::endl;
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
	}
}

void onMouseMotion(int X, int Y) {
}

void onReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	screenWidth = w;
	screenHeight = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, screenWidth/screenHeight, 0.0001, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void ColorShift(Color c, long len, long when) {
	SHR.add(new shifter<Color>(&(level.c_strip[0]), c*0.6, (long)len, (long)when));
	SHR.add(new shifter<Color>(&(level.c_strip[1]), c*0.3, (long)len, (long)when));
	SHR.add(new shifter<Color>(&(level.c_hexagon), c*0.9, (long)len, (long)when));
	SHR.add(new shifter<Color>(&(level.c_hexagon_inside), c*0.45, (long)len, (long)when));
	SHR.add(new shifter<Color>(&(level.c_player), c, (long)len, (long)when));	
}

void onIdle( ) {
	movePlayer();

	long time = glutGet(GLUT_ELAPSED_TIME);
	level.extra_angle = 10;
	ColorShift(c_red, (long)200, (long)200);
	ColorShift(c_blue, (long)3000, (long)3000);
	ColorShift(c_red, (long)3000, (long)6000);
	ColorShift(c_blue, (long)3000, (long)9000);
	ColorShift(c_red, (long)3000, (long)12000);
	ColorShift(c_green, (long)3000, (long)15000);
	ColorShift(c_yellow, (long)3000, (long)18000);
	ColorShift(c_green, (long)3000, (long)21000);
	ColorShift(c_yellow, (long)3000, (long)24000);
	ColorShift(c_blue, (long)3000, (long)27000);
	ColorShift(c_red, (long)3000, (long)30000);
	ColorShift(c_blue, (long)3000, (long)33000);
	ColorShift(c_red, (long)3000, (long)36000);
	ColorShift(c_green, (long)3000, (long)39000);
	ColorShift(c_yellow, (long)3000, (long)42000);
	ColorShift(c_green, (long)3000, (long)45000);
	ColorShift(c_yellow, (long)3000, (long)48000);

	SHR.shift();
	if(level.playing)
	blocklist.shift();

	camera.rotate(0.35*sin(time/800.0));
	camera.distance(1 + sin(time/800.0));
	camera.height(18+3*sin(time/300.0)*sin(time/200.0));
	onDisplay();
}

void onInitialization( ) {
	c_time = p_time = 0;
	glViewport(0, 0, screenWidth, screenHeight);
}

int main(int argc, char **argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Hexagon");
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	onInitialization();
	glutDisplayFunc(onDisplay);
	glutMouseFunc(onMouse);
	glutIdleFunc(onIdle);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onKeyboard);
	glutKeyboardUpFunc(onKeyboardUp);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutMotionFunc(onMouseMotion);
	glutFullScreen();

	glutMainLoop();
	return 0;
}
