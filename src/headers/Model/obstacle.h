#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "textures.h"
#include "../GUI/gameWindow.h"

class Obstacle {
	public:
		Obstacle(int locX = -1, int locY = -1, int code = DEFAULT_OBSTACLE);
		const int &getCode() const {return code;}
		const int &getX() const {return x;}
		const int &getY() const {return y;}
		const bool &isBroken() const {return broken;}
		const bool &isSolid() const {return solid;}
		void setLocation(const int newX, const int newY) {x=newX;y=newY;} 

		sf::Sprite &getSpriteEntire() {return spriteEntire;}
		sf::Sprite &getSpriteBroken() {return spriteBroken;}

		//Load element that don't need to be serialized
		void loadSprite();

		//Method which contains standard properties of an obstacle
		void generalObstacle();
		void tableA();

		template<class Archive>
	    void save(Archive& ar, const unsigned int version) const {
	        ar & code & x & y & broken;
	    }
	    template<class Archive>
	    void load(Archive& ar, const unsigned int version) {
	        ar & code & x & y & broken;
	        loadSprite();
	    }
	    BOOST_SERIALIZATION_SPLIT_MEMBER();

	private:
		int code;
		int x;
		int y;
		bool broken;
		bool solid;
		sf::Sprite spriteEntire;
		sf::Sprite spriteBroken;
};

BOOST_CLASS_VERSION(Obstacle, 6);

#endif