#ifndef CELL_H
#define CELL_H

#include "../utils/lib.h"
#include "../utils/const.h"

#include "textures.h"
#include "item.h"
#include "mapExit.h"
#include "obstacle.h"
#include "door.h"

class Cell {
	public:
		Cell();
		Cell(int code);
		const int &getCode() const {return code;}
		bool isSolid();
		bool isTransparent();
		const bool &isViewed() const {return viewed;}
		const bool &isVisited() const {return visited;}
		void setVisited(const bool &newVisited) {visited=newVisited;}
		void setViewed(const bool &newViewed) {viewed=newViewed;}
		sf::Sprite &getSprite() {return sprite;}

		//If drawSolid == true, we only draw solid cells
		void draw(const int x, const int y, bool drawSolid);
		//Load element that don't need to be serialized
		void loadSprite();

		//These methods get the standard properties of an element
		void nothing();
		void dungeonFloorA();
		void dungeonWallA();
		void dungeonWallItemA();
		void dungeonExit();
		void cavernFloorA();
		void cavernWallA();
		void grassA();
		void treeA();

		//The drops are items contains on the cell
		std::vector<Item> drops;
		//This vector may contains a way to an another map
		std::vector<MapExit> exits;
		//This vector constains all obstacles (like furnitures)
		std::vector<Obstacle> obstacles;

		std::vector<Door> doors;

		template<class Archive>
	    void save(Archive& ar, const unsigned int version) const {
	        ar & code & visited & drops & exits & obstacles & doors;
	    }
		template<class Archive>
	    void load(Archive& ar, const unsigned int version){
	        ar & code & visited & drops & exits & obstacles & doors;
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