#include "../headers/Model/cell.h"

Cell::Cell() {
	this->code = NOTHING_CODE;
	this->solid = true;
	this->transparent = false;
	this->visited = false;
	this->viewed = false;
	this->sprite.setTexture(Textures::texturesFloors);
	this->sprite.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
}

Cell::Cell(int code) {
	switch (code) {
		case DUNGEON_FLOOR_A:
			dungeonFloorA();
			break;
		case DUNGEON_WALL_A:
			dungeonWallA();
			break;
		default:
			Cell();
	}
}

void Cell::loadSprite() {
	switch (code) {
		case DUNGEON_FLOOR_A:
			this->solid = false;
			this->transparent = true;
			this->sprite.setTexture(Textures::texturesFloors);
			this->sprite.setTextureRect(sf::IntRect(0, T_TILES, T_TILES, T_TILES));
			break;
		case DUNGEON_WALL_A:
			this->solid = true;
			this->transparent = false;
			this->sprite.setTexture(Textures::texturesWalls);
			this->sprite.setTextureRect(sf::IntRect(0, 0, T_TILES+4, T_TILES+4));
			break;
		default:
			this->solid = true;
			this->transparent = false;
			this->sprite.setTexture(Textures::texturesFloors);
			this->sprite.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
	}
}

void Cell::dungeonFloorA() {
	this->code = DUNGEON_FLOOR_A;
	this->solid = false;
	this->transparent = true;
	this->visited = false;
	this->viewed = false;
	this->sprite.setTexture(Textures::texturesFloors);
	this->sprite.setTextureRect(sf::IntRect(0, T_TILES, T_TILES, T_TILES));
}

void Cell::dungeonWallA() {
	this->code = DUNGEON_WALL_A;
	this->solid = true;
	this->transparent = false;
	this->visited = false;
	this->viewed = false;
	this->sprite.setTexture(Textures::texturesWalls);
	this->sprite.setTextureRect(sf::IntRect(0, 0, T_TILES+4, T_TILES+4));
}