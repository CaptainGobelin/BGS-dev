#include "../headers/Model/door.h"

//////////////General description///////////////////////

Door::Door(int locX/* = -1*/, int locY/* = -1*/, int code/* = DEFAULT_ITEM*/) {
	this->code = code;
	this->x = locX;
	this->y = locY;
	this->open = true;
	loadSprite();
}

bool Door::isTransparent() {
	return this->open || this->transparent;
}

void Door::draw(int x, int y) {
	if (isOpen()) {
		getSpriteOpen().setPosition((x+11.5)*T_TILES,(y+11.5)*T_TILES);
		GameWindow::window.draw(getSpriteOpen());
	}
	else {
		getSpriteClose().setPosition((x+11.5)*T_TILES,(y+11.5)*T_TILES);
		GameWindow::window.draw(getSpriteClose());
	}
}

void Door::openDoor() {
	this->open = true;
}

void Door::loadSprite() {
	switch (code) {
		case DUNGEON_DOOR_A:
			dungeonDoorA();
			break;
		default:
			generalDoor();
	}
}

void Door::doorFactory(int code, bool transparent, sf::Vector2i pos_clos, sf::Vector2i offset_clos,
	sf::Vector2i pos_op, sf::Vector2i offset_op) {
	this->code = code;
	this->transparent = transparent;
	this->spriteOpen.setTexture(Textures::texturesDoors);
	this->spriteOpen.setTextureRect(sf::IntRect(pos_op, offset_op));
	this->spriteClose.setTexture(Textures::texturesDoors);
	this->spriteClose.setTextureRect(sf::IntRect(pos_clos, offset_clos));
}

void Door::generalDoor() {
	doorFactory(DEFAULT_DOOR, false, sf::Vector2i(0, 0), sf::Vector2i(1, 1),
		sf::Vector2i(0, 0), sf::Vector2i(1, 1));
}

void Door::dungeonDoorA() {
	doorFactory(DUNGEON_DOOR_A, false, sf::Vector2i(0, 0), sf::Vector2i(T_TILES, T_TILES),
		sf::Vector2i(0, T_TILES), sf::Vector2i(T_TILES, T_TILES));
}