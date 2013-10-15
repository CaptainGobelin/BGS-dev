#ifndef STR_UTILS_H
#define STR_UTILS_H

#include "lib.h"
#include "const.h"

class StringUtils {
	public:
		//Convert a string to a file name string (use for save files)
		static std::string saveStem(std::string s);
		//Map file are named after 3 component (X_X_X)
		//These method return the desired component of the given code
		static int getMapCode(std::string mapCode, int component);
};

#endif