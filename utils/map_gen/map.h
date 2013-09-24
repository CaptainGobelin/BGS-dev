#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>

#define L_WINDOW 992
#define H_WINDOW 672

class Map {
	public :
		Map();
		Map(int newX, int newY);
		~Map();

		int **cell;
		int x;
		int y;
};

#endif