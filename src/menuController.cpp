#include "headers/menuController.h"

MenuController::MenuController() {}

int MenuController::launch() {
	int choice = 0;
	menuScreen.display(choice);
	GameInput input;
	do {
		input = this->menuScreen.recupInput();
		switch (input.getValue()) {
			case CLOSE_INPUT:
				return input.getValue();
			case DOWN_INPUT:
				choice = (choice+1)%4;
				menuScreen.display(choice);
				break;
			case UP_INPUT:
				choice--;
				while (choice < 0)
					choice += 4;
				menuScreen.display(choice);
				break;
		}
	} while (input.getValue() != ENTER_INPUT);
	if (choice == 1) {
		LoadGameMenuController loadGameMenu;
		Interface interface;
		std::string charName = "";
		loadGameMenu.launch(&charName);
		Character character = SaveUtils::load(charName, interface);
		SessionController sessionController;
		return sessionController.launch(character, interface);
	}
	return CLOSE_INPUT;
}