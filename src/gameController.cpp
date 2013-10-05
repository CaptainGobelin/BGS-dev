#include "headers/gameController.h"

GameController::GameController() {
	//Rand initialization
	srand (time(NULL));
	//Load the game config
	OptionsFile gameOptions;
	gameOptions.load();
	//Load textures
	Textures::loadTextures(TEXTURES_PATH);
	//Open the window
	GameWindow::setOptions(gameOptions);
}

void GameController::launch() {
	int choice = INIT_CHOICE;
	while (choice != CLOSE_INPUT) {
		switch (choice) {
			case CLOSE_INPUT: {
				return;
			}
			case INIT_CHOICE: {
				choice = startScreen();
				break;
			}
			case TO_MAIN_MENU: {
				choice = mainMenu();
				break;
			}

		}
	}
}

int GameController::startScreen() {
	//Launch the start screen
	StartController startController;
	return startController.launch();
}

int GameController::mainMenu() {
	MenuController menuController;
	return menuController.launch();
}