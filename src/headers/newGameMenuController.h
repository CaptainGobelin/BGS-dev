#ifndef CNEW_MENU_H
#define CNEW_MENU_H

#include "utils/lib.h"
#include "utils/const.h"

#include "utils/mapGenerator.h"
#include "GUI/newGameMenuScreen.h"

class NewGameMenuController {
	public:
		NewGameMenuController();
		int launch(std::string &name);
		void createCharacter(std::string name);

	private:
		NewGameMenuScreen newGameMenuScreen;
		std::list<std::string> characters;
};

#endif