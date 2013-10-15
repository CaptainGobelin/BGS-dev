#ifndef PATTERN_H
#define PATTERN_H

#include "lib.h"
#include "const.h"

#include "mapPrototype.h"
#include "nameGenerator.h"

class MapPattern {
	public :
		MapPattern();
		int flood(MapPrototype &map);
		void flood_rec(MapPrototype &map, int fX, int fY);
		virtual void apply(MapPrototype &map) = 0;
		virtual std::string getRandomName() = 0;
};

class Random : public MapPattern {
	public : 
		Random();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
};

class Cavern : public MapPattern {
	public : 
		Cavern();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
	private :
		void apply_loop(MapPrototype &map);
};

class Labyrinth : public MapPattern {
	public : 
		Labyrinth();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
	private :
		void apply_backtrack(MapPrototype &map, int cX, int cY);
		void remove_dead_end(MapPrototype &map);
		bool is_dead_end(MapPrototype &map, int i, int j);
};

class Dungeon : public MapPattern {
	public : 
		Dungeon();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
	private :
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