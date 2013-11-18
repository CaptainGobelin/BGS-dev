#ifndef MAP_GEN_U_H
#define MAP_Gen_U_H
#include <SFML/Graphics.hpp>
#include "map.h"

class MapGenUtils {
	public:
		static bool canAddWall(Map &map, int x, int y);
};

#endif