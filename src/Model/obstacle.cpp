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

void Obstacle::obstacleFactory(int code, bool solid, sf::Vector2i pos_ent, sf::Vector2i offset_ent,
			sf::Vector2i pos_brok, sf::Vector2i offset_brok) {
	this->code = code;
	this->solid = solid;
	this->spriteEntire.setTexture(Textures::texturesObstacles);
	this->spriteEntire.setTextureRect(sf::IntRect(pos_ent, offset_ent));
	this->spriteBroken.setTexture(Textures::texturesObstacles);
	this->spriteBroken.setTextureRect(sf::IntRect(pos_brok, offset_brok));
}

void Obstacle::generalObstacle() {
	obstacleFactory(DEFAULT_OBSTACLE, false, sf::Vector2i(0, 0), sf::Vector2i(1, 1),
		sf::Vector2i(0, 0), sf::Vector2i(1, 1));
}

void Obstacle::tableA() {
	obstacleFactory(TABLE_A, true, sf::Vector2i(0, 0), sf::Vector2i(T_TILES, T_TILES),
		sf::Vector2i(0, T_TILES), sf::Vector2i(T_TILES, T_TILES));
}