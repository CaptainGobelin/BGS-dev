#ifndef VMAP_H
#define VMAP_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "gameInput.h"
#include "../Model/textures.h"
#include "gameWindow.h"
#include "../Model/character.h"
#include "../Model/map.h"

class MapScreen {
	public:
		MapScreen();

		const sf::Sprite &getMapSprite() const {return mapSprite;}
		const sf::Sprite &getCharSprite() const {return charSprite;}
		const sf::Sprite &getBlocSprite() const {return blocSprite;}
		const sf::Sprite &getEmptySprite() const {return emptySprite;}

		//Scale the map sprite to fill the entire screen
		void setScale(int mLength, int mWidth);
		GameInput recupInput();
		void display(Map &map, Character &character);

	private:
		sf::Font font;
		sf::Sprite mapSprite;
		sf::Sprite charSprite;
		sf::Sprite blocSprite;
		sf::Sprite emptySprite;
		sf::Text mapName;
		int mapLength;
		int mapWidth;
};

#endif