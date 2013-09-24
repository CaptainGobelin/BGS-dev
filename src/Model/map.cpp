#include "../headers/Model/map.h"

Map::Map() {
	this->length = 0;
	this->width = 0;
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
      		if (cell[i][j].isViewed())
      			cell[i][j].setViewed(false);
}

void Map::draw(const int x, const int y) {
	GameWindow::window.setView(GameWindow::viewGame);
	for (int i=std::max(0,x-12);i<std::min(length,x+13);i++)
      	for (int j=std::max(0,y-12);j<std::min(width,y+13);j++) {
      		if (!cell[i][j].isVisited())
      			continue;
			cell[i][j].getSprite().setPosition((i-x+11.5)*T_TILES,(j-y+11.5)*T_TILES);
			if (cell[i][j].isSolid())
				continue;
			GameWindow::window.draw(cell[i][j].getSprite());
			if (cell[i][j].drops.empty())
				continue;
			for (std::list<Item>::reverse_iterator it=cell[i][j].drops.rbegin();it!=cell[i][j].drops.rend();++it) {
				(*it).getSpriteOff().setPosition((i-x+11.5)*T_TILES,(j-y+11.5)*T_TILES);
				GameWindow::window.draw((*it).getSpriteOff());
			}
		}
	for (int i=std::max(0,x-12);i<std::min(length,x+13);i++)
      	for (int j=std::max(0,y-12);j<std::min(width,y+13);j++) {
      		if (!cell[i][j].isVisited())
      			continue;
				if (cell[i][j].isSolid())
					GameWindow::window.draw(cell[i][j].getSprite());
				if (!cell[i][j].isViewed()) {
					fog.setPosition((i-x+11.5)*T_TILES,(j-y+11.5)*T_TILES);
					GameWindow::window.draw(fog);
				}
		}
}