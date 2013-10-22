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
		case GRASS_A:
			grassA();
			break;
		case TREE_A:
			treeA();
			break;
		default:
			nothing();
	}
}

void Cell::wallFactory(int c, bool s, bool t, int x0, int y0, int x1, int y1) {
	this->code = c;
	this->solid = s;
	this->transparent = t;
	this->sprite.setTexture(Textures::texturesWalls);
	this->sprite.setTextureRect(sf::IntRect(x0, y0, x1, y1));
}

void Cell::floorFactory(int c, bool s, bool t, int x0, int y0, int x1, int y1) {
	this->code = c;
	this->solid = s;
	this->transparent = t;
	this->sprite.setTexture(Textures::texturesFloors);
	this->sprite.setTextureRect(sf::IntRect(x0, y0, x1, y1));
}

void Cell::nothing() {
	floorFactory(NOTHING_CODE, true, false, 0, 0, T_TILES, T_TILES);
}

void Cell::dungeonFloorA() {
	floorFactory(DUNGEON_FLOOR_A, false, true, 0, T_TILES, T_TILES, T_TILES);
}

void Cell::dungeonWallA() {
	wallFactory(DUNGEON_WALL_A, true, false, 0, 0, T_TILES+4, T_TILES+4);
}

void Cell::dungeonExit() {
	floorFactory(DUNGEON_EXIT, false, true, 0, 3*T_TILES, T_TILES, T_TILES);
}

void Cell::cavernWallA() {
	wallFactory(CAVERN_WALL_A, true, false, T_TILES+4, 0, T_TILES+4, T_TILES+4);
}

void Cell::cavernFloorA() {
	floorFactory(CAVERN_FLOOR_A, false, true, T_TILES, 0, T_TILES, T_TILES);
}

void Cell::grassA() {
	floorFactory(GRASS_A, false, true, T_TILES, T_TILES, T_TILES, T_TILES);
}

void Cell::treeA() {
	wallFactory(TREE_A, true, false, 2*(T_TILES+4), 0, T_TILES+4, T_TILES+4);
}