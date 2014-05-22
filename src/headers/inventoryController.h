#ifndef CINVENTORY_H
#define CINVENTORY_H

#include "utils/lib.h"
#include "utils/const.h"

#include "Model/textures.h"
#include "GUI/inventoryScreen.h"

class InventoryController {
	public:
		InventoryController();
		int launch(Character &character);

	private:
		InventoryScreen inventoryScreen;
};

#endif