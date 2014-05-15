#ifndef PATTERN_H
#define PATTERN_H

#include "lib.h"
#include "const.h"

#include "mapPrototype.h"
#include "nameGenerator.h"
#include "../Model/cell.h"

//Each pattern sub-class is a type of map we can generate.

class MapPattern {
	public:
		MapPattern();
		//Apply simply generate a map prototype of the pattern
		virtual void apply(MapPrototype &map) = 0;
		virtual std::string getRandomName() = 0;
		virtual void floorCell(Cell &cell) = 0;
		virtual void wallCell(Cell &cell) = 0;
		virtual void wallItemCell(Cell &cell) = 0;
		//Add the specify number of "walls"
		void addWalls(MapPrototype &map, int k);
	protected:
		//The flood method will remove floors we can't access
		//flood return the number of accessible floors
		int flood(MapPrototype &map);
		void flood_rec(MapPrototype &map, int fX, int fY);
		//Cavern generator algorithm
		//toWall controls the number of walls (low value for more walls)
		//limit controls the width of corridor (4 for small corridors, 5 for large)
		//loop controls the sharpness of the map (4 for "natural" walls for example)
		void cavernGenerator(MapPrototype &map, int toWall, int limit, int loop);
		//Check if we don't block a floor while adding wall
		bool canAddWall(MapPrototype &map, int x, int y);
};

class Random : public MapPattern {
	public: 
		Random();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
		virtual void floorCell(Cell &cell);
		virtual void wallCell(Cell &cell);
		virtual void wallItemCell(Cell &cell);
};

#endif