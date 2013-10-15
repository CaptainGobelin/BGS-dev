#ifndef NAMEGEN_H
#define NAMEGEN_H

#include "lib.h"
#include "const.h"

#include "human_analyze.h"

class NameGenerator {
	public:
		static std::string humanName();
		static std::string dungeonName();

	private:
		static std::string getAdjectif();
		static std::string getName();
		static std::string getAdjectifName();
};

#endif