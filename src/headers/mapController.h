#ifndef CMAP_H
#define CMAP_H

#include "utils/lib.h"
#include "utils/const.h"

#include "Model/textures.h"
#include "GUI/mapScreen.h"

class MapController {
	public:
		MapController(Map &map, Character &character);
		int launch(Map &map, Character &character);

	private:
		MapScreen mapScreen;
};

#endif