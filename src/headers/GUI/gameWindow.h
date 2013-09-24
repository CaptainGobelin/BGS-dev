#ifndef WINDOW_H
#define WINDOW_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "../optionsFile.h"

class GameWindow {
	public :
		static void setOptions(OptionsFile opt);
		
		static sf::RenderWindow window;
		static sf::View viewGame;
		static sf::View viewInt;
};

#endif
