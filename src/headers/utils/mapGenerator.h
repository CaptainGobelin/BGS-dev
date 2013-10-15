#ifndef MAPGEN_H
#define MAPGEN_H

#include "lib.h"
#include "const.h"

#include "stringUtils.h"
#include "../Model/map.h"
#include "mapPattern.h"

class MapGenerator {
	public:
		//The map generator neeed a pattern (dungeon, forest, maze, etc...)
		//Map code is the name of the save file of the map
		static Map generate(int x, int y, MapPattern *pattern, std::string mapCode);
};

#endif