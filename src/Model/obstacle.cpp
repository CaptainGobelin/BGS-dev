#include "../headers/Model/obstacle.h"

//////////////General description///////////////////////

Obstacle::Obstacle(int locX/* = -1*/, int locY/* = -1*/, int code/* = DEFAULT_ITEM*/) {
	this->code = code;
	this->x = locX;
	this->y = locY;
	this->broken = false;
	loadSprite();
}

void Obstacle::broke() {
	this->broken = true;
	this->solid = false;
}

void Obstacle::loadSprite() {
	switch (code) {
		case TABLE_A:
			tableA();
			break;
		default:
			generalObstacle();
	}
}

void Obstacle::generalObstacle() {
	this->code = DEFAULT_OBSTACLE;
	this->spriteEntire.setTexture(Textures::texturesObstacles);
	this->spriteEntire.setTextureRect(sf::IntRect(0, 0, 1, 1));
	this->spriteBroken.setTexture(Textures::texturesObstacles);
	this->spriteBroken.setTextureRect(sf::IntRect(0, 0, 1, 1));
}

void Obstacle::tableA() {
	this->code = TABLE_A;
	this->solid = true;
	this->spriteEntire.setTexture(Textures::texturesObstacles);
	this->spriteEntire.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
	this->spriteBroken.setTexture(Textures::texturesObstacles);
	this->spriteBroken.setTextureRect(sf::IntRect(0, T_TILES, T_TILES, T_TILES));
}