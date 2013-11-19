#include "../headers/Model/map.h"

Map::Map(int x/*=0*/, int y/*=0*/) {
	this->length = x;
	this->width = y;
	cell = new Cell* [length];
   			for (int i=0;i<length;i++)
        		cell[i] = new Cell [width];
	this->fog.setTexture(Textures::texturesFloors);
	this->fog.setTextureRect(sf::IntRect(0, 2*T_TILES, T_TILES, T_TILES));
}

Map::~Map() {
	for (int i = 0; i < this->length; i++)
		delete [] this->cell[i];
	delete [] this->cell;
}

void Map::refreshCells(const int x, const int y) {
	for (int i=std::max(0,x-12);i<std::min(length,x+13);i++)
      	for (int j=std::max(0,y-12);j<std::min(width,y+13);j++)
      		if (cell[i][j].isViewed()) {
      			cell[i][j].setViewed(false);
      		}
}

void Map::draw(const int x, const int y) {
	//First we draw the floors (sprite, the items)
	GameWindow::window.setView(GameWindow::viewGame);
	for (int i=std::max(0,x-12);i<std::min(length,x+13);i++)
      	for (int j=std::max(0,y-12);j<std::min(width,y+13);j++) {
			cell[i][j].draw(i-x, j-y, false);
		}
	//And then the wall (cause sprites are bigger)
	for (int i=std::max(0,x-12);i<std::min(length,x+13);i++)
      	for (int j=std::max(0,y-12);j<std::min(width,y+13);j++) {
			cell[i][j].draw(i-x, j-y, true);
			if (!cell[i][j].isViewed()) {
				fog.setPosition((i-x+11.5)*T_TILES,(j-y+11.5)*T_TILES);
				GameWindow::window.draw(fog);
			}
		}
}