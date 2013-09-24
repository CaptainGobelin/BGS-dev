#ifndef CLOAD_MENU_H
#define CLOAD_MENU_H

#include "utils/lib.h"
#include "utils/const.h"

class LoadGameMenuController {
	public :
		LoadGameMenuController();
		int launch(std::string *charName);
};

#endif