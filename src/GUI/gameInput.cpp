#include "../headers/GUI/gameInput.h"

GameInput::GameInput() {
	value = INVALID_INPUT;
}

void GameInput::treatEvent(sf::Event event) {
	if (event.type == sf::Event::Closed) {
		value = CLOSE_INPUT;
		return;
	}
	else if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == OptionsFile::mapKey) {
			value = M_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::upKey) {
			value = UP_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::downKey) {
			value = DOWN_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::rightKey) {
			value = RIGHT_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::leftKey) {
			value = LEFT_INPUT;
			return;
		}
		else switch (event.key.code) {
			case sf::Keyboard::Q : {value=Q_INPUT;return;}
			case sf::Keyboard::Return : {value=ENTER_INPUT;return;}
			case sf::Keyboard::Escape : {value=ESCAPE_INPUT;return;}
			case sf::Keyboard::Delete : {value=DELETE_INPUT;return;}
			default : {value=ANY_KEY_INPUT;return;}
		}
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