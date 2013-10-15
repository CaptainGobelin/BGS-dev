#ifndef CGAME_H
#define CGAME_H

#include "utils/lib.h"
#include "utils/const.h"

#include "optionsFile.h"
#include "GUI/gameWindow.h"
#include "Model/textures.h"
#include "Model/character.h"
#include "startController.h"
#include "menuController.h"
#include "utils/saveUtils.h"
#include "Model/map.h"

class GameController {
	public:
		GameController();
		void launch();

	private:
		int startScreen();
		int mainMenu();
};

#endif
