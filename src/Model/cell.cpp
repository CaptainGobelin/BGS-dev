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

bool Cell::isSolid() {
	if (!this->obstacles.empty())
		return this->obstacles.begin()->isSolid() || this->solid;
	else
		return this->solid;
}

void Cell::draw(const int x, const int y, bool drawSolid) {
	if (!this->visited)
		return;
	if (this->solid != drawSolid)
		return;
	this->sprite.setPosition((x+11.5)*T_TILES,(y+11.5)*T_TILES);
	GameWindow::window.draw(this->sprite);
	if (!this->drops.empty())
		for (std::list<Item>::reverse_iterator it=this->drops.rbegin();it!=this->drops.rend();++it) {
			(*it).getSpriteOff().setPosition((x+11.5)*T_TILES,(y+11.5)*T_TILES);
			GameWindow::window.draw((*it).getSpriteOff());
		}
	if (!this->obstacles.empty())
		if (this->obstacles.begin()->isBroken()) {
			this->obstacles.begin()->getSpriteBroken().setPosition((x+11.5)*T_TILES,(y+11.5)*T_TILES);
			GameWindow::window.draw(this->obstacles.begin()->getSpriteBroken());
		}
		else {
			this->obstacles.begin()->getSpriteEntire().setPosition((x+11.5)*T_TILES,(y+11.5)*T_TILES);
			GameWindow::window.draw(this->obstacles.begin()->getSpriteEntire());
		}
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
		case DUNGEON_WALL_ITEM_A:
			dungeonWallItemA();
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

void Cell::dungeonWallItemA() {
	wallFactory(DUNGEON_WALL_ITEM_A, true, false, 0, T_TILES+4, T_TILES, T_TILES);
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