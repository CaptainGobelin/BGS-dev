#ifndef WINDOW_H
#define WINDOW_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "../optionsFile.h"

class GameWindow {
	public:
		static void setOptions();
		
		static sf::RenderWindow window;
		//Game viewport
		static sf::View viewGame;
		//Interface viewport
		static sf::View viewInt;
};

#endif
