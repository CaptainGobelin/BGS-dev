#include "../headers/GUI/newGameMenuScreen.h"

NewGameMenuScreen::NewGameMenuScreen() {
	font.loadFromFile((std::string)FONT_PATH+"pcsenior.ttf");
	characterName.setFont(font);
	characterName.setCharacterSize(20);
	characterName.setColor(sf::Color::White);
	characterName.setPosition(10,10);
	warning.setFont(font);
	warning.setColor(sf::Color::Red);
	warning.setPosition(10,40);
	warning.setString("Invalid name");
}

sf::Event NewGameMenuScreen::recupInput() {
	sf::Event event;
	GameWindow::window.waitEvent(event);
	return event;
}

void NewGameMenuScreen::display(bool correct) {
	GameWindow::window.clear();
	GameWindow::window.draw(characterName);
	if (!correct)
		GameWindow::window.draw(warning);
	GameWindow::window.display();
}