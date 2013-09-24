#ifndef ITEM_H
#define ITEM_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "textures.h"
#include "../GUI/gameWindow.h"

class Item {
	public :
		Item();
		Item(int locX, int locY);
		const int &getType() const {return type;}
		const int &getX() const {return x;}
		const int &getY() const {return y;}
		void setLocation(const int newX, const int newY) {x=newX;y=newY;} 
		const std::string &getName() const {return name;}
		void setName(const std::string &newName) {name=newName;}
		sf::Sprite &getSpriteOn() {return spriteOn;}
		sf::Sprite &getSpriteOff() {return spriteOff;}

	protected :
		int type;
		int x;
		int y;
		std::string name;
		sf::Sprite spriteOn;
		sf::Sprite spriteOff;
	};

class Sword1HA : public Item {
	public : 
		Sword1HA();
		Sword1HA(int locX, int locY);
};

class GreavesLA : public Item {
	public : 
		GreavesLA();
		GreavesLA(int locX, int locY);
};

#endif