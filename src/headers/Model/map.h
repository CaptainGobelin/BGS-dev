#ifndef MAP_H
#define MAP_H

#include "../utils/lib.h"
#include "../utils/const.h"

#include "cell.h"
#include "textures.h"
#include "../GUI/gameWindow.h"

class Map {
	public :
		Map();
		~Map();
		const int &getLength() const {return length;}
		void setLength(const int &newLength) {length=newLength;}
		const int &getWidth() const {return width;}
		void setWidth(const int &newWidth) {width=newWidth;}

		void refreshCells(const int x, const int y);
		void draw(const int x, const int y);

		Cell **cell;
		sf::Sprite fog;

	private :
		int length;
		int width;
};

#endif