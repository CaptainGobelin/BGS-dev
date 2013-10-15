#ifndef GINPUT_H
#define GINPUT_H

#include "../utils/const.h"
#include "../utils/lib.h"

//GameInput convert an SFML event to a value and reject invalid inputs

class GameInput {
	public:
		GameInput();
		const unsigned int &getValue() const {return value;}
		void setValue(const unsigned int &newValue) {value=newValue;}

		void treatEvent(sf::Event event);
		bool isValid();

	private:
		unsigned int value;
};

#endif
