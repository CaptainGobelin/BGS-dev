#ifndef DOOR_H
#define DOOR_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "textures.h"
#include "../GUI/gameWindow.h"

class Door {
	public:
		Door(int locX = -1, int locY = -1, int code = DEFAULT_DOOR);
		const int &getCode() const {return code;}
		const int &getX() const {return x;}
		const int &getY() const {return y;}
		const bool &isOpen() const {return open;}

		void setLocation(const int newX, const int newY) {x=newX;y=newY;} 

		sf::Sprite &getSpriteOpen() {return spriteOpen;}
		sf::Sprite &getSpriteClose() {return spriteClose;}

		bool isTransparent();

		void draw(int x, int y);

		void openDoor();

		//Load element that don't need to be serialized
		void loadSprite();

		//Factories
		void doorFactory(int code, bool transparent, sf::Vector2i pos_clos, sf::Vector2i offset_clos,
			sf::Vector2i pos_op, sf::Vector2i offset_op);

		//Method which contains standard properties of an obstacle
		void generalDoor();
		void dungeonDoorA();

		template<class Archive>
	    void save(Archive& ar, const unsigned int version) const {
	        ar & code & x & y & open;
	    }
	    template<class Archive>
	    void load(Archive& ar, const unsigned int version) {
	        ar & code & x & y & open;
	        loadSprite();
	    }
	    BOOST_SERIALIZATION_SPLIT_MEMBER();

	private:
		int code;
		int x;
		int y;
		bool open;
		bool transparent;
		sf::Sprite spriteOpen;
		sf::Sprite spriteClose;
};

BOOST_CLASS_VERSION(Door, 7);

#endif