#ifndef CSESSION_H
#define CSESSION_H

#include "utils/lib.h"
#include "utils/const.h"

#include "Model/textures.h"
#include "Model/character.h"
#include "Model/interface.h"
#include "utils/saveUtils.h"
#include "utils/mapGenerator.h"
#include "Model/map.h"
#include "GUI/sessionScreen.h"
#include "mapController.h"
#include "inventoryController.h"


class SessionController {
	public:
		SessionController();
		int launch(Character &character, Interface &interface);
		bool changeMap(Character &character, Map &map, Interface &interface);
};

#endif