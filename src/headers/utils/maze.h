#ifndef MAZE_PAT_H
#define MAZE_PAT_H

#include "lib.h"
#include "const.h"

#include "mapPrototype.h"
#include "nameGenerator.h"
#include "../Model/cell.h"

#include "mapPattern.h"

class Maze : public MapPattern {
	public: 
		Maze();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
		virtual void floorCell(Cell &cell);
		virtual void wallCell(Cell &cell);
		virtual void wallItemCell(Cell &cell);
	private:
		void apply_backtrack(MapPrototype &map, int cX, int cY);
		void remove_dead_end(MapPrototype &map);
		bool is_dead_end(MapPrototype &map, int i, int j);
};

#endif