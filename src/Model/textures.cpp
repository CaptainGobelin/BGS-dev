#include "../headers/Model/textures.h"

void Textures::loadTextures(const char *path) {
	texturesStart.loadFromFile(path+(std::string)"int/titlePage1.png");
	texturesCharacters.loadFromFile(path+(std::string)"tiles/char.png");
	texturesFloors.loadFromFile(path+(std::string)"tiles/floor.png");
	texturesWalls.loadFromFile(path+(std::string)"tiles/wall.png");
	texturesArmorOn.loadFromFile(path+(std::string)"tiles/armor_on.png");
	texturesArmorOff.loadFromFile(path+(std::string)"tiles/armor_off.png");
	texturesWeaponOn.loadFromFile(path+(std::string)"tiles/weapon_on.png");
	texturesWeaponOff.loadFromFile(path+(std::string)"tiles/weapon_off.png");
	texturesObstacles.loadFromFile(path+(std::string)"tiles/obstacles.png");
	texturesInterface.loadFromFile(path+(std::string)"int/panel.png");
	texturesMap.loadFromFile(path+(std::string)"int/mParch.png");
	texturesMenu.loadFromFile(path+(std::string)"int/menuPan.png");
}
