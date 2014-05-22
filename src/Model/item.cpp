#include "../headers/Model/item.h"

//////////////General description///////////////////////

Item::Item(int locX/* = -1*/, int locY/* = -1*/, int code/* = DEFAULT_ITEM*/) {
	this->code = code;
	this->x = locX;
	this->y = locY;
	loadSprite();
}

void Item::draw(int x, int y) {
	getSpriteOff().setPosition((x+11.5)*T_TILES,(y+11.5)*T_TILES);
	GameWindow::window.draw(getSpriteOff());
}

void Item::loadSprite() {
	switch (code) {
		case SWORD_1H_A:
			sword1HA();
			break;
		case GREAVES_L_A:
			greavesLA();
			break;
		default:
			generalItem();
	}
}

void Item::weaponFactory(std::string name, int code, sf::Vector2i pos_off, sf::Vector2i offset_off,
			sf::Vector2i pos_on, sf::Vector2i offset_on) {
	this->name = name;
	this->code = code;
	this->spriteOn.setTexture(Textures::texturesWeaponOn);
	this->spriteOn.setTextureRect(sf::IntRect(pos_on, offset_on));
	this->spriteOff.setTexture(Textures::texturesWeaponOff);
	this->spriteOff.setTextureRect(sf::IntRect(pos_off, offset_off));
}

void Item::armorFactory(std::string name, int code, sf::Vector2i pos_off, sf::Vector2i offset_off,
			sf::Vector2i pos_on, sf::Vector2i offset_on) {
	this->name = name;
	this->code = code;
	this->spriteOn.setTexture(Textures::texturesArmorOn);
	this->spriteOn.setTextureRect(sf::IntRect(pos_on, offset_on));
	this->spriteOff.setTexture(Textures::texturesArmorOff);
	this->spriteOff.setTextureRect(sf::IntRect(pos_off, offset_off));
}

void Item::generalItem() {
	weaponFactory("", DEFAULT_ITEM, sf::Vector2i(0, 0), sf::Vector2i(1, 1),
		sf::Vector2i(0, 0), sf::Vector2i(1, 1));
}

//////////////1H Weapons description///////////////////////

void Item::sword1HA() {
	weaponFactory("Sword", SWORD_1H_A, sf::Vector2i(0, 0), sf::Vector2i(T_TILES, T_TILES), 
		sf::Vector2i(0, 0), sf::Vector2i(T_TILES, T_TILES));
}

//////////////Greaves Ligth description///////////////////////

void Item::greavesLA() {
	armorFactory("Loin Cloth", GREAVES_L_A, sf::Vector2i(0, 0), sf::Vector2i(T_TILES, T_TILES), 
		sf::Vector2i(0, 0), sf::Vector2i(T_TILES, T_TILES));
}