#ifndef MAP_PROTO_H
#define MAP_PROTO_H

#include "lib.h"
#include "const.h"

class MapPrototype {
	public :
		MapPrototype();
		MapPrototype(int newX, int newY);
		~MapPrototype();

		int **cell;
		int x;
		int y;
};

#endif