#ifndef MAPGEN_H
#define MAPGEN_H

#include "lib.h"
#include "const.h"

#include "../Model/map.h"
#include "mapPattern.h"

class MapGenerator {
	public :
		static Map generate(int x, int y, MapPattern *pattern);
};

#endif