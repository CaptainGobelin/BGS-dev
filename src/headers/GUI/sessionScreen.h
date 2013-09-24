#ifndef VSESSION_H
#define VSESSION_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "gameInput.h"
#include "../Model/textures.h"
#include "../Model/character.h"
#include "../Model/map.h"
#include "../Model/interface.h"
#include "gameWindow.h"

class SessionScreen {
	public :
		SessionScreen();

		GameInput recupInput();
		void display(Character& character, Interface& interface, Map &map);
};

#endif