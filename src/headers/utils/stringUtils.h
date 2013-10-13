#ifndef STR_UTILS_H
#define STR_UTILS_H

#include "lib.h"
#include "const.h"

class StringUtils {
	public :
		static std::string saveStem(std::string s);
		static int getMapCode(std::string mapCode, int component);
};

#endif