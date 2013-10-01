#ifndef CMENU_H
#define CMENU_H

#include "utils/lib.h"
#include "utils/const.h"

#include "Model/textures.h"
#include "Model/character.h"
#include "utils/saveUtils.h"
#include "Model/map.h"
#include "loadGameMenuController.h"
#include "sessionController.h"
#include "GUI/menuScreen.h"

class MenuController {
	public :
		MenuController();
		int launch();

	private :
		MenuScreen menuScreen;
};

#endif