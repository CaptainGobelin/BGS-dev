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
};

class Cavern : public MapPattern {
	public: 
		Cavern();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
		virtual void floorCell(Cell &cell);
		virtual void wallCell(Cell &cell);
};

class Plain : public MapPattern {
	public: 
		Plain();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
		virtual void floorCell(Cell &cell);
		virtual void wallCell(Cell &cell);
};

class Labyrinth : public MapPattern {
	public: 
		Labyrinth();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
		virtual void floorCell(Cell &cell);
		virtual void wallCell(Cell &cell);
	private:
		void apply_backtrack(MapPrototype &map, int cX, int cY);
		void remove_dead_end(MapPrototype &map);
		bool is_dead_end(MapPrototype &map, int i, int j);
};

class Dungeon : public MapPattern {
	public: 
		Dungeon();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
		virtual void floorCell(Cell &cell);
		virtual void wallCell(Cell &cell);
	private:
		void apply_loop(MapPrototype &map);
		bool draw_room(MapPrototype &map, int i, int j, int &maxI, int &maxJ);
		void draw_entries(MapPrototype &map, int i, int j, int maxI, int maxJ);
		void draw_corridor(MapPrototype &map, int i, int j);
		void remove_dead_end(MapPrototype &map);
		void remove_corridor(MapPrototype &map, int i, int j);
		int dirI(int dir);
		int dirJ(int dir);
};

#endif