#ifndef CNEW_MENU_H
#define CNEW_MENU_H

#include "utils/lib.h"
#include "utils/const.h"

#include "GUI/newGameMenuScreen.h"

class NewGameMenuController {
	public :
		NewGameMenuController();
		int launch();

	private :
		NewGameMenuScreen newGameMenuScreen;
		std::list<std::string> characters;
};

#endif