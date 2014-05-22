#include "../headers/GUI/inventoryScreen.h"

InventoryScreen::InventoryScreen() {
	this->font.loadFromFile((std::string)FONT_PATH+"mapFont.ttf");
	this->panelSprite.setTexture(Textures::texturesInventory);
	this->panelSprite.setTextureRect(sf::IntRect(0, 0, 950, 560));
	this->panelSprite.setPosition(21,21);
}

GameInput InventoryScreen::recupInput() {
	sf::Event event;
	GameInput input;
	while (!input.isValid()) {
		GameWindow::window.waitEvent(event);
		input.treatEvent(event);
	}
	return input;
}

void InventoryScreen::display(Character &character) {
	GameWindow::window.draw(this->panelSprite);
	GameWindow::window.display();
}