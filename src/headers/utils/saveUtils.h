#ifndef SAVE_H
#define SAVE_H

#include "lib.h"
#include "const.h"

#include "../Model/character.h"
#include "../Model/interface.h"
#include "../Model/map.h"

class SaveUtils {
	public :
		static void save(const Character character);
		static Character load(std::string name, Interface &interface);
		static Map loadMap(std::string charName, std::string mapName);

	private :
		static std::string serialize(const Race *race);
};

#endif