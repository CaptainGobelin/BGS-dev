#ifndef PATTERN_H
#define PATTERN_H

#include "map.h"

class Pattern {
	public :
		Pattern();
		int flood(Map &map);
		void flood_rec(Map &map, int fX, int fY);
		virtual void apply(Map &map) = 0;
};

class Random : public Pattern {
	public : 
		Random();
		virtual void apply(Map &map);
};

class Cavern : public Pattern {
	public : 
		Cavern();
		virtual void apply(Map &map);
	private :
		void apply_loop(Map &map);
};

class Labyrinth : public Pattern {
	public : 
		Labyrinth();
		virtual void apply(Map &map);
	private :
		void apply_backtrack(Map &map, int cX, int cY);
};

class Dungeon : public Pattern {
	public : 
		Dungeon();
		virtual void apply(Map &map);
	private :
		void apply_loop(Map &map);
		bool draw_room(Map &map, int i, int j, int &maxI, int &maxJ);
		void draw_entries(Map &map, int i, int j, int maxI, int maxJ);
		void draw_corridor(Map &map, int i, int j);
		void remove_dead_end(Map &map);
		void remove_corridor(Map &map, int i, int j);
		int dirI(int dir);
		int dirJ(int dir);
};

#endif