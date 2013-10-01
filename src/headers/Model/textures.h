#ifndef TEXTURES_H
#define TEXTURES_H

#include "../utils/const.h"
#include "../utils/lib.h"

class Textures {
	public :
		static void loadTextures(const char *path);
		static sf::Texture texturesStart;
		static sf::Texture texturesCharacters;
		static sf::Texture texturesFloors;
		static sf::Texture texturesWalls;
		static sf::Texture texturesArmorOn;
		static sf::Texture texturesArmorOff;
		static sf::Texture texturesWeaponOn;
		static sf::Texture texturesWeaponOff;
		static sf::Texture texturesInterface;
		static sf::Texture texturesMap;
		static sf::Texture texturesMenu;
};

#endif
