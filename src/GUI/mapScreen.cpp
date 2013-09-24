#include "../headers/GUI/mapScreen.h"

MapScreen::MapScreen() {
	this->mapSprite.setTexture(Textures::texturesMap);
	this->blocSprite.setTexture(Textures::texturesMap);
	this->emptySprite.setTexture(Textures::texturesMap);
	this->charSprite.setTexture(Textures::texturesMap);
	this->mapSprite.setTextureRect(sf::IntRect(0, 0, 950, 630));
	this->blocSprite.setTextureRect(sf::IntRect(0, 630, 50, 50));
	this->emptySprite.setTextureRect(sf::IntRect(50, 630, 50, 50));
	this->charSprite.setTextureRect(sf::IntRect(100, 630, 50, 50));
	this->mapSprite.setPosition(21,21);
	this->mapLength = 1;
	this->mapWidth = 1;
}

void MapScreen::setScale(int mLength, int mWidth) {
	this->mapLength = mLength;
	this->mapWidth = mWidth;
	float pX = 774/(float)mLength;
	float pY = 500/(float)mWidth;
	float scale = std::min(pX,pY)/50;
	this->blocSprite.setScale(scale,scale);
	this->emptySprite.setScale(scale,scale);
	this->charSprite.setScale(scale,scale);
}

GameInput MapScreen::recupInput() {
	sf::Event event;
	GameInput input;
	while (!input.isValid()) {
		GameWindow::window.waitEvent(event);
		input.treatEvent(event);
	}
	return input;
}

void MapScreen::display(Map &map, Character &character) {
	int pix = this->blocSprite.getScale().x * 50;
	GameWindow::window.draw(this->mapSprite);
	for (int i=-this->mapLength/2;i<(this->mapLength+1)/2;i++)
		for (int j=-this->mapWidth/2;j<(this->mapWidth+1)/2;j++) {
			if (map.cell[i+this->mapLength/2][j+this->mapWidth/2].isVisited()) {
				if (map.cell[i+this->mapLength/2][j+this->mapWidth/2].isSolid()) {
					this->blocSprite.setPosition(503+pix*i,369+pix*j);
					GameWindow::window.draw(this->blocSprite);
				}
				else {
					this->emptySprite.setPosition(503+pix*i,369+pix*j);
					GameWindow::window.draw(this->emptySprite);
				}
			}
		}
	this->charSprite.setPosition(503+pix*(character.getX()-this->mapLength/2),\
		369+pix*(character.getY()-this->mapWidth/2));
	GameWindow::window.draw(this->charSprite);
	GameWindow::window.display();
}