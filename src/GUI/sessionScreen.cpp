#include "../headers/GUI/sessionScreen.h"

SessionScreen::SessionScreen() {}

GameInput SessionScreen::recupInput() {
	sf::Event event;
	GameInput input;
	while (!input.isValid()) {
		GameWindow::window.waitEvent(event);
		input.treatEvent(event);
	}
	return input;
}

void SessionScreen::display(Character& character, Interface& interface, Map &map) {
	GameWindow::window.clear();
	map.draw(character.getX(), character.getY());
	character.draw();
	interface.draw();
	GameWindow::window.display();
}