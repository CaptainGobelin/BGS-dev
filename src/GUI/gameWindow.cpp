#include "../headers/GUI/gameWindow.h"

void GameWindow::setOptions() {
	window.create(sf::VideoMode(L_WINDOW, H_WINDOW, 32), "Blood, Gold and Sorcery");
	window.setVerticalSyncEnabled(OptionsFile::vSync);
	window.setFramerateLimit(OptionsFile::frameLimit);
	viewGame.reset(sf::FloatRect(0, 0, L_WINDOW-320, H_WINDOW));
	viewGame.setViewport(sf::FloatRect(0, 0, 0.677419355f, 1.f));
	viewInt.reset(sf::FloatRect(0, 0, L_WINDOW, H_WINDOW));
	window.setView(viewInt);
}
