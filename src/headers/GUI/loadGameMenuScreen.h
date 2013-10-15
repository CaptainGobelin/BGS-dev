#ifndef VLOAD_H
#define VLOAD_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "gameInput.h"
#include "gameWindow.h"
#include "../utils/saveUtils.h"
#include "../Model/interface.h"
#include "../Model/character.h"

class LoadGameMenuScreen {
	public:
		LoadGameMenuScreen();

		//Get the number of character saved
		int getNChoices();
		//Get the name of a character
		std::string getName(int choice);
		GameInput recupInput();
		void display(int choice);

	private:
		std::list<sf::Text> characters;
		sf::Font font;
};

#endif