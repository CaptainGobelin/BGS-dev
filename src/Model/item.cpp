#include "../headers/Model/item.h"

//////////////General description///////////////////////

Item::Item() {
	this->name = "";
	this->type = DEFAULT_ITEM;
	this->x = -1;
	this->y = -1;
	this->spriteOn.setTexture(Textures::texturesWeaponOn);
	this->spriteOn.setTextureRect(sf::IntRect(0, 0, 1, 1));
	this->spriteOff.setTexture(Textures::texturesWeaponOff);
	this->spriteOff.setTextureRect(sf::IntRect(0, 0, 1, 1));
}

//////////////1H Weapons description///////////////////////

Sword1HA::Sword1HA() {
	this->name = "Sword";
	this->type = SWORD_1H_A;
	this->x = -1;
	this->y = -1;
	this->spriteOn.setTexture(Textures::texturesWeaponOn);
	this->spriteOn.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
	this->spriteOff.setTexture(Textures::texturesWeaponOff);
	this->spriteOff.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
}

//////////////Greaves Ligth description///////////////////////

GreavesLA::GreavesLA() {
	this->name = "Loin cloth";
	this->type = GREAVES_L_A;
	this->x = -1;
	this->y = -1;
	this->spriteOn.setTexture(Textures::texturesArmorOn);
	this->spriteOn.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
	this->spriteOff.setTexture(Textures::texturesArmorOff);
	this->spriteOff.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
}


///////////////////Loaded items constructor////////////////////////////

//////////////General description///////////////////////

Item::Item(int locX, int locY) {
	this->name = "";
	this->type = DEFAULT_ITEM;
	this->x = locX;
	this->y = locY;
	this->spriteOn.setTexture(Textures::texturesWeaponOn);
	this->spriteOn.setTextureRect(sf::IntRect(0, 0, 1, 1));
	this->spriteOff.setTexture(Textures::texturesWeaponOff);
	this->spriteOff.setTextureRect(sf::IntRect(0, 0, 1, 1));
}

//////////////1H Weapons description///////////////////////

Sword1HA::Sword1HA(int locX, int locY) {
	this->name = "Sword";
	this->type = SWORD_1H_A;
	this->x = locX;
	this->y = locY;
	this->spriteOn.setTexture(Textures::texturesWeaponOn);
	this->spriteOn.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
	this->spriteOff.setTexture(Textures::texturesWeaponOff);
	this->spriteOff.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
}

//////////////Greaves Ligth description///////////////////////

GreavesLA::GreavesLA(int locX, int locY) {
	this->name = "Loin cloth";
	this->type = GREAVES_L_A;
	this->x = locX;
	this->y = locY;
	this->spriteOn.setTexture(Textures::texturesArmorOn);
	this->spriteOn.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
	this->spriteOff.setTexture(Textures::texturesArmorOff);
	this->spriteOff.setTextureRect(sf::IntRect(0, 0, T_TILES, T_TILES));
}