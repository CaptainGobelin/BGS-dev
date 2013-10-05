#include "../headers/GUI/gameInput.h"

GameInput::GameInput() {
	value = INVALID_INPUT;
}

void GameInput::treatEvent(sf::Event event) {
	if (event.type == sf::Event::Closed) {
		value = CLOSE_INPUT;
		return;
	}
	else if (event.type == sf::Event::KeyPressed)
		switch (event.key.code) {
			case sf::Keyboard::Up : {value=UP_INPUT;return;}
			case sf::Keyboard::Down : {value=DOWN_INPUT;return;}
			case sf::Keyboard::Right : {value=RIGHT_INPUT;return;}
			case sf::Keyboard::Left : {value=LEFT_INPUT;return;}
			case sf::Keyboard::M : {value=M_INPUT;return;}
			case sf::Keyboard::Return : {value=ENTER_INPUT;return;}
			case sf::Keyboard::Escape : {value=ESCAPE_INPUT;return;}
			default : {value=ANY_KEY_INPUT;return;}
		}
	else {
		value = INVALID_INPUT;
		return;
	}
}

bool GameInput::isValid() {
	if (value == INVALID_INPUT)
		return false;
	else 
		return true;
}