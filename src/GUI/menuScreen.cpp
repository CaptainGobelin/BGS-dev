#include "../headers/GUI/menuScreen.h"

MenuScreen::MenuScreen() {
	this->titleScreen.setTexture(Textures::texturesStart);
	this->titleScreen.setPosition(0,0);
	GameWindow::window.draw(titleScreen);
	GameWindow::window.display();
	this->menuPanel.setTexture(Textures::texturesMenu);
	this->menuPanel.setTextureRect(sf::IntRect(0, 0, 252, 190));
	this->menuPanel.setPosition(370,450);
	this->arrow.setTexture(Textures::texturesMenu);
	this->arrow.setTextureRect(sf::IntRect(0, 190, 35, 30));
	this->arrow.setPosition(377,478);
	this->font.loadFromFile((std::string)FONT_PATH+"pcsenior.ttf");
	for (int i=0;i<4;i++) {
		this->textBox[i].setFont(font);
		this->textBox[i].setCharacterSize(22);
		this->textBox[i].setColor(sf::Color::Black);
		this->textBox[i].setPosition(415, 477+i*34);
	}
	this->textBox[0].setString("New Game");
	this->textBox[1].setString("Load Game");
	this->textBox[2].setString("Options");
	this->textBox[3].setString("Exit");
}

GameInput MenuScreen::recupInput() {
	sf::Event event;
	GameInput input;
	while (!input.isValid()) {
		GameWindow::window.waitEvent(event);
		input.treatEvent(event);
	}
	return input;
}

void MenuScreen::display(int choice) {
	GameWindow::window.draw(menuPanel);
	this->arrow.setPosition(377,478+34*choice);
	GameWindow::window.draw(arrow);
	for (int i=0;i<4;i++)
		GameWindow::window.draw(this->textBox[i]);
	GameWindow::window.display();
}