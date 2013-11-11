#ifndef OPTIONS_H
#define OPTIONS_H

#include "utils/const.h"
#include "utils/lib.h"

class OptionsFile {
	public:
		static bool load();
		static int frameLimit;
		static bool vSync;
		static sf::Keyboard::Key mapKey;
		static sf::Keyboard::Key upKey;
		static sf::Keyboard::Key downKey;
		static sf::Keyboard::Key rightKey;
		static sf::Keyboard::Key leftKey;

	private:
		static void setOption(std::string line);
		static bool toBool(std::string const& s);
		static sf::Keyboard::Key toKey(std::string const& s);
};

#endif
