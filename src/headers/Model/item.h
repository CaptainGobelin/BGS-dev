#ifndef ITEM_H
#define ITEM_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "textures.h"
#include "../GUI/gameWindow.h"

class Item {
	public :
		Item(int locX = -1, int locY = -1, int code = DEFAULT_ITEM);
		const int &getCode() const {return code;}
		const int &getX() const {return x;}
		const int &getY() const {return y;}
		void setLocation(const int newX, const int newY) {x=newX;y=newY;} 
		const std::string &getName() const {return name;}
		void setName(const std::string &newName) {name=newName;}
		sf::Sprite &getSpriteOn() {return spriteOn;}
		sf::Sprite &getSpriteOff() {return spriteOff;}

		void loadSprite();

		void generalItem();
		void sword1HA();
		void greavesLA();

	protected :
		int code;
		int x;
		int y;
		std::string name;
		sf::Sprite spriteOn;
		sf::Sprite spriteOff;
	};

#endif