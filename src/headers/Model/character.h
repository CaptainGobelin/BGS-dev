#ifndef CHAR_H
#define CHAR_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "race.h"
#include "map.h"
#include "item.h"
#include "textures.h"
#include "../GUI/gameWindow.h"

class Character {
	public :
		Character();
		Character(std::string, int raceChoice, std::string map);
		const Race &getRace() const {return race;}
		void setRace(const Race &newRace) {race=newRace;}
		const std::string &getName() const {return name;}
		void setName(const std::string &newName) {name=newName;}
		const int &getX() const {return x;}
		void setX(const int &newX) {x=newX;}
		const int &getY() const {return y;}
		void setY(const int &newY) {y=newY;}
		const std::string &getMap() const {return map;}
		void setMap(const std::string &newMap) {map=newMap;}

		void draw();
		bool move(int dX, int dY, const Map& map);
		void setPosition(int newX, int newY) {setX(newX);setY(newY);}
		void checkView(Map& map);

		std::list<Item> inventory;

	private :
		std::string name;
		Race race;
		int attributes[2];
		int x;
		int y;
		std::string map;

		void checkVer(Map& map, int dir);
		void checkHor(Map& map, int dir);
};

#endif