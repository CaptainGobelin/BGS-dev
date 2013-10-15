#ifndef VSTART_H
#define VSTART_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "gameInput.h"
#include "../Model/textures.h"
#include "gameWindow.h"

class StartScreen {
	public:
		StartScreen();
		const sf::Sprite &getTitleScreen() const {return titleScreen;}
		void setTitleScreen(const sf::Sprite &newTitleScreen) {titleScreen=newTitleScreen;}

		GameInput recupInput();
		void display();

	private:
		sf::Sprite titleScreen;
};

#endif
