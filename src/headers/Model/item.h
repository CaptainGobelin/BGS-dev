#ifndef ITEM_H
#define ITEM_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "textures.h"
#include "../GUI/gameWindow.h"

class Item {
	public:
		Item(int locX = -1, int locY = -1, int code = DEFAULT_ITEM);
		const int &getCode() const {return code;}
		const int &getX() const {return x;}
		const int &getY() const {return y;}
		void setLocation(const int newX, const int newY) {x=newX;y=newY;} 
		const std::string &getName() const {return name;}
		void setName(const std::string &newName) {name=newName;}
		sf::Sprite &getSpriteOn() {return spriteOn;}
		sf::Sprite &getSpriteOff() {return spriteOff;}

		void draw(int x, int y);

		//Load element that don't need to be serialized
		void loadSprite();

		//Factories
		void weaponFactory(std::string name, int code, sf::Vector2i pos_off, sf::Vector2i offset_off,
			sf::Vector2i pos_on, sf::Vector2i offset_on);
		void armorFactory(std::string name, int code, sf::Vector2i pos_off, sf::Vector2i offset_off,
			sf::Vector2i pos_on, sf::Vector2i offset_on);

		//Method which contains standard properties of an item
		void generalItem();
		void sword1HA();
		void greavesLA();

		template<class Archive>
	    void save(Archive& ar, const unsigned int version) const {
	        ar & code & x & y;
	    }
	    template<class Archive>
	    void load(Archive& ar, const unsigned int version) {
	        ar & code & x & y;
	        loadSprite();
	    }
	    BOOST_SERIALIZATION_SPLIT_MEMBER();

	private:
		int code;
		int x;
		int y;
		std::string name;
		//Sprite of the item if equiped
		sf::Sprite spriteOn;
		//Sprite of the item if unequiped
		sf::Sprite spriteOff;
	};

BOOST_CLASS_VERSION(Item, 6);

#endif