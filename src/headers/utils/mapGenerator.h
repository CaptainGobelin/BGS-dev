#ifndef MAPGEN_H
#define MAPGEN_H

#include "lib.h"
#include "const.h"

#include "stringUtils.h"
#include "../Model/map.h"
#include "mapPattern.h"
#include "nameGenerator.h"

class MapGenerator {
	public :
		static Map generate(int x, int y, MapPattern *pattern, std::string mapCode);
};

#endif