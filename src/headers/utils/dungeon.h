#ifndef DUNGEON_PAT_H
#define DUNGEON_PAT_H

#include "lib.h"
#include "const.h"

#include "mapPrototype.h"
#include "nameGenerator.h"
#include "../Model/cell.h"
#include "rooms.h"

#include "mapPattern.h"

class Dungeon : public MapPattern {
	public: 
		Dungeon();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
		virtual void floorCell(Cell &cell);
		virtual void doorCell(Cell &cell);
		virtual void wallCell(Cell &cell);
		virtual void wallItemCell(Cell &cell);
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