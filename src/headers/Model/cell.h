#ifndef CELL_H
#define CELL_H

#include "../utils/lib.h"
#include "../utils/const.h"

#include "textures.h"
#include "item.h"
#include "mapExit.h"

class Cell {
	public:
		Cell();
		Cell(int code);
		const int &getCode() const {return code;}
		const bool &isSolid() const {return solid;}
		const bool &isTransparent() const {return transparent;}
		const bool &isViewed() const {return viewed;}
		const bool &isVisited() const {return visited;}
		void setVisited(const bool &newVisited) {visited=newVisited;}
		void setViewed(const bool &newViewed) {viewed=newViewed;}
		sf::Sprite &getSprite() {return sprite;}

		//Load element that don't need to be serialized
		void loadSprite();

		//These methods get the standard properties of an element
		void nothing();
		void dungeonFloorA();
		void dungeonWallA();
		void dungeonExit();
		void cavernFloorA();
		void cavernWallA();

		//The drops are items contains on the cell
		std::list<Item> drops;
		//This list may contains a way to an another map
		std::list<MapExit> exits;

		template<class Archive>
	    void save(Archive& ar, const unsigned int version) const {
	        ar & code & visited & drops & exits;
	    }
		template<class Archive>
	    void load(Archive& ar, const unsigned int version){
	        ar & code & visited & drops & exits;
	        loadSprite();
	    }
	    BOOST_SERIALIZATION_SPLIT_MEMBER();

	private:
		int code;
		bool solid;
		bool transparent;
		bool viewed;
		bool visited;
		sf::Sprite sprite;

		void wallFactory(int c, bool s, bool t, int x0, int y0, int x1, int y1);
		void floorFactory(int c, bool s, bool t, int x0, int y0, int x1, int y1);
};

BOOST_CLASS_VERSION(Cell, 4);

#endif