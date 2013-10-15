#ifndef VNEW_H
#define VNEW_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "gameInput.h"
#include "gameWindow.h"
#include "../utils/saveUtils.h"
#include "../Model/interface.h"
#include "../Model/character.h"

class NewGameMenuScreen {
	public:
		NewGameMenuScreen();

		sf::Event recupInput();
		void display(bool correct);

		sf::Text characterName;

	private:
		sf::Font font;
		sf::Text warning;
};

#endif