#ifndef _BLOCKLIST_H
#define _BLOCKLIST_H

#include <list>

class Block {
public:
	Block(int s = 0, double d = 3);
	int strip;
	double d_block;
	double c_offset;
	double c_offset_base;
};

class BlockList {
	double dist_per_msec;
public:
	long prev_time;
	std::list<Block> blocks;
	BlockList(double _dist_per_msec = 0.008);
	void add(Block b);
	void shift();
};

void BlockTypeA(BlockList& blocklist, int distance, int n_gon = 6);
void BlockTypeB(BlockList& blocklist, int distance, int n_gon = 6);
void BlockTypeC(BlockList& blocklist, int distance, int hole, int n_gon = 6);
void BlockTypeS(BlockList& blocklist, int distance, int n_gon = 6);

#endif
