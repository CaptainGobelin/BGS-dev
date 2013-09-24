#ifndef CELL_H
#define CELL_H

#include "../utils/lib.h"
#include "../utils/const.h"

#include "textures.h"
#include "item.h"

class Cell {
	public :
		Cell();
		const int &getCode() const {return code;}
		const bool &isSolid() const {return solid;}
		const bool &isTransparent() const {return transparent;}
		const bool &isViewed() const {return viewed;}
		const bool &isVisited() const {return visited;}
		void setVisited(const bool &newVisited) {visited=newVisited;}
		void setViewed(const bool &newViewed) {viewed=newViewed;}
		sf::Sprite &getSprite() {return sprite;}

		std::list<Item> drops;

	protected :
		int code;
		bool solid;
		bool transparent;
		bool viewed;
		bool visited;
		sf::Sprite sprite;
};

class DungeonFloorA : public Cell {
	public : 
		DungeonFloorA();
};

class DungeonWallA : public Cell {
	public :
		DungeonWallA();
};

#endif