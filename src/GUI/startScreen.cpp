#include "../headers/GUI/startScreen.h"

StartScreen::StartScreen() {
	this->titleScreen.setTexture(Textures::texturesStart);
	this->titleScreen.setPosition(0,0);
}

GameInput StartScreen::recupInput() {
	sf::Event event;
	GameInput input;
	while (!input.isValid()) {
		GameWindow::window.waitEvent(event);
		input.treatEvent(event);
	}
	return input;
}

void StartScreen::display() {
	GameWindow::window.draw(this->titleScreen);
	GameWindow::window.display();
}