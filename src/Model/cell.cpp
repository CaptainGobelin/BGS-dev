#include "../headers/Model/cell.h"

Cell::Cell() {
	this->visited = false;
	this->viewed = false;
	nothing();
}

Cell::Cell(int code) {
	this->code = code;
	this->visited = false;
	this->viewed = false;
	loadSprite();
}

void Cell::loadSprite() {
	this->viewed = false;
	switch (code) {
		case DUNGEON_FLOOR_A:
			dungeonFloorA();
			break;
		case DUNGEON_WALL_A:
			dungeonWallA();
			break;
		case DUNGEON_EXIT:
			dungeonExit();
			break;
		case CAVERN_FLOOR_A:
			cavernFloorA();
			break;
		case CAVERN_WALL_A:
			cavernWallA();
			break;
		default:
			nothing();
	}
}

void Cell::nothing() {
	this->code = NOTHING_CODE;
	this->solid = true;
	this->transparent = false;
	this->sprite.setTexture(Textures::texturesFloors);
	this->sprite.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
}

void Cell::dungeonFloorA() {
	this->code = DUNGEON_FLOOR_A;
	this->solid = false;
	this->transparent = true;
	this->sprite.setTexture(Textures::texturesFloors);
	this->sprite.setTextureRect(sf::IntRect(0, T_TILES, T_TILES, T_TILES));
}

void Cell::dungeonWallA() {
	this->code = DUNGEON_WALL_A;
	this->solid = true;
	this->transparent = false;
	this->sprite.setTexture(Textures::texturesWalls);
	this->sprite.setTextureRect(sf::IntRect(0, 0, T_TILES+4, T_TILES+4));
}

void Cell::dungeonExit() {
	this->code = DUNGEON_EXIT;
	this->solid = false;
	this->transparent = true;
	this->sprite.setTexture(Textures::texturesFloors);
	this->sprite.setTextureRect(sf::IntRect(0, 3*T_TILES, T_TILES, T_TILES));
}

void Cell::cavernWallA() {
	this->code = CAVERN_WALL_A;
	this->solid = true;
	this->transparent = false;
	this->sprite.setTexture(Textures::texturesWalls);
	this->sprite.setTextureRect(sf::IntRect(T_TILES+4, 0, T_TILES+4, T_TILES+4));
}

void Cell::cavernFloorA() {
	this->code = CAVERN_FLOOR_A;
	this->solid = false;
	this->transparent = true;
	this->sprite.setTexture(Textures::texturesFloors);
	this->sprite.setTextureRect(sf::IntRect(T_TILES, 0, T_TILES, T_TILES));
}