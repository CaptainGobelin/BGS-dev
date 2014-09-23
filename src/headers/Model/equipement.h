#ifndef EQUIP_H
#define EQUIP_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "item.h"
#include "textures.h"
#include "../GUI/gameWindow.h"

class Equipement {
	public:
		Equipement();
		const int &getX() const {return x;}
		void setX(const int &newX) {x=newX;}
		const int &getY() const {return y;}
		void setY(const int &newY) {y=newY;}

		void draw();
		void setPosition(int newX, int newY) {setX(newX);setY(newY);}

		Item *legs;

	    template<class Archive>
	    void save(Archive& ar, const unsigned int version) const {
	        //ar & x & y & legs;
	        /*if (legs)
	        	ar & true & legs;
	        else
	        	ar & false;*/
	    }
	    template<class Archive>
	    void load(Archive& ar, const unsigned int version){
	        ar & x & y;
	        //legs = new Item;
	        //ar & legs;
	    }
	    BOOST_SERIALIZATION_SPLIT_MEMBER();

	private:
		int x;
		int y;
};

BOOST_CLASS_VERSION(Equipement, 200);

#endif