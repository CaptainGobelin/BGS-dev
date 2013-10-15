#ifndef INTERFACE_H
#define INTERFACE_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "textures.h"
#include "map.h"
#include "../GUI/gameWindow.h"

class Interface {
	public:
		Interface();

		const std::string getMessage(int i) const;
		void write(std::string message);
		void draw();
		//Show the list of the items of a cell
		void showItems(Cell &cell);
		//Show the way to an another map if there's one
		void showDestination(Cell & cell);

	private:
		sf::Sprite panel;
		sf::Font font;
		sf::Text textBox[MESS_LINES];
};

#endif