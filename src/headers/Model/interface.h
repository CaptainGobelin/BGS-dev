#ifndef INTERFACE_H
#define INTERFACE_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "textures.h"
#include "map.h"
#include "../GUI/gameWindow.h"

class Interface {
	public :
		Interface();

		void write(std::string message);
		void draw();
		void showItems(Cell &cell);

	private :
		sf::Sprite panel;
		sf::Font font;
		sf::Text textBox[MESS_LINES];
};

#endif