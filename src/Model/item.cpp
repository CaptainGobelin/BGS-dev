#include "../headers/Model/item.h"

//////////////General description///////////////////////

Item::Item(int locX/* = -1*/, int locY/* = -1*/, int code/* = DEFAULT_ITEM*/) {
	this->code = code;
	this->x = locX;
	this->y = locY;
	loadSprite();
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

void Item::generalItem() {
	this->name = "";
	this->code = DEFAULT_ITEM;
	this->spriteOn.setTexture(Textures::texturesWeaponOn);
	this->spriteOn.setTextureRect(sf::IntRect(0, 0, 1, 1));
	this->spriteOff.setTexture(Textures::texturesWeaponOff);
	this->spriteOff.setTextureRect(sf::IntRect(0, 0, 1, 1));
}

//////////////1H Weapons description///////////////////////

void Item::sword1HA() {
	this->name = "Sword";
	this->code = SWORD_1H_A;
	this->spriteOn.setTexture(Textures::texturesWeaponOn);
	this->spriteOn.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
	this->spriteOff.setTexture(Textures::texturesWeaponOff);
	this->spriteOff.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
}

//////////////Greaves Ligth description///////////////////////

void Item::greavesLA() {
	this->name = "Loin cloth";
	this->code = GREAVES_L_A;
	this->spriteOn.setTexture(Textures::texturesArmorOn);
	this->spriteOn.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
	this->spriteOff.setTexture(Textures::texturesArmorOff);
	this->spriteOff.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
}