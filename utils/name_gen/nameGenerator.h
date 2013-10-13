#ifndef NAME_GEN_H
#define NAME_GEN_H

#include <cstdlib>
#include <string>

#include "human_analyze.h"

class NameGenerator {
	public :
		NameGenerator();

		std::string generate();
};

#endif