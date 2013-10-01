#ifndef VEMNU_H
#define VMENU_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "gameInput.h"
#include "../Model/textures.h"
#include "gameWindow.h"

class MenuScreen {
	public :
		MenuScreen();
		const sf::Sprite &getMenuPanel() const {return menuPanel;}
		const sf::Sprite &getArrow() const {return arrow;}

		GameInput recupInput();
		void display(int choice);

	private :
		sf::Sprite menuPanel;
		sf::Sprite arrow;
		sf::Text textBox[4];
		sf::Font font;
};

#endif
