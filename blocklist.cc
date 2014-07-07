#include <ctime>
#include <cmath>
#include <cstdlib>

#include <GL/glut.h>

#include "blocklist.h"

Block::Block(int s, double d) {
	strip = s;
	d_block = d;
	c_offset_base = (rand() % 600 + 1);
	c_offset = fabs(sin(c_offset_base));
}

BlockList::BlockList(double _dist_per_msec) {
	dist_per_msec = _dist_per_msec;
	prev_time = 0;
}
void BlockList::add(Block b) {
	blocks.push_back(b);
}
void BlockList::shift() {
	long c_time = glutGet(GLUT_ELAPSED_TIME);
	long elapsed_time = c_time - prev_time;
	for(std::list<Block>::iterator i = blocks.begin(); i != blocks.end(); ++i) {
		(*i).d_block -= dist_per_msec * elapsed_time;
		(*i).c_offset = fabs(sin((c_time + (*i).c_offset_base)/600.0));
	}
	for(std::list<Block>::iterator i = blocks.begin(); i != blocks.end(); ++i) {
		if((*i).d_block <= 0.0) {
			blocks.erase(i);
			i = blocks.begin();
		}
	}
	prev_time = c_time;
}

void BlockTypeA(BlockList& blocklist, int distance, int n_gon) {
	blocklist.add(Block(rand() % n_gon, distance));
}
void BlockTypeB(BlockList& blocklist, int distance, int n_gon) {
	blocklist.add(Block(rand() % n_gon, distance + (rand()%10)/5.0));
}
void BlockTypeC(BlockList& blocklist, int distance, int hole, int n_gon) {
	for(int i = 0; i < n_gon; ++i)
		if(i!=hole)
			blocklist.add(Block(i, distance));
}
void BlockTypeS(BlockList& blocklist, int distance, int n_gon) {
	for(int i = 0; i < 20; ++i) {
			blocklist.add(Block(i%n_gon, distance + i*0.75));
	}
}
