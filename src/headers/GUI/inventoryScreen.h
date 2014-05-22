#ifndef VINVENTORY_H
#define VINVENTORY_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "gameInput.h"
#include "../Model/textures.h"
#include "gameWindow.h"
#include "../Model/character.h"

class InventoryScreen {
	public:
		InventoryScreen();

		const sf::Sprite &getPanelSprite() const {return panelSprite;}

		GameInput recupInput();
		void display(Character &character);

	private:
		sf::Font font;
		sf::Sprite panelSprite;
};

#endif