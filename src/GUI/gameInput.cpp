#include "../headers/GUI/gameInput.h"

GameInput::GameInput() {
	value = INVALID_INPUT;
}

void GameInput::treatEvent(sf::Event event) {
	if (event.type == sf::Event::Closed) {
		value = CLOSE_INPUT;
		return;
	}
	else if (event.type == sf::Event::GainedFocus) {
		GameWindow::window.display();
		return;
	}
	else if (event.type == sf::Event::LostFocus) {
		GameWindow::window.display();
		return;
	}
	else if (event.type == sf::Event::Resized) {
		GameWindow::window.display();
		return;
	}
	else if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == OptionsFile::mapGameKey) {
			value = M_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::inventoryGameKey) {
			value = I_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::upGameKey) {
			value = UP_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::downGameKey) {
			value = DOWN_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::rightGameKey) {
			value = RIGHT_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::leftGameKey) {
			value = LEFT_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::menuGameKey) {
			value = ESCAPE_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::validGameKey) {
			value = ENTER_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::exitGameKey) {
			value = Q_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::confirmGameKey) {
			value = Y_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::cancelGameKey) {
			value = N_INPUT;
			return;
		}
		if (event.key.code == OptionsFile::pickGameKey) {
			value = P_INPUT;
			return;
		}
		switch (event.key.code) {
			case sf::Keyboard::Delete : {value=DELETE_INPUT;return;}
			default : {value=ANY_KEY_INPUT;return;}
		}
		value = ANY_KEY_INPUT;
		return;
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