#ifndef CELL_H
#define CELL_H

#include "../utils/lib.h"
#include "../utils/const.h"

#include "textures.h"
#include "item.h"
#include "mapExit.h"

class Cell {
	public :
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

		void loadSprite();

		void nothing();
		void dungeonFloorA();
		void dungeonWallA();
		void dungeonExit();

		std::list<Item> drops;
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

	protected :
		int code;
		bool solid;
		bool transparent;
		bool viewed;
		bool visited;
		sf::Sprite sprite;
};

BOOST_CLASS_VERSION(Cell, 4);

#endif