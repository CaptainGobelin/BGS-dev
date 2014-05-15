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
			case ESCAPE_INPUT:
				return INIT_CHOICE;
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
	//When you choose an option in the menu:
	//If you press new game, you create a character
	//And then the game load it
	if (choice == 0) {
		NewGameMenuController newGameMenuController;
		std::string charName = "";
		int toDo = newGameMenuController.launch(charName);
		//If toDo contains an other value than TO_CONTNIUE, we
		//Stop the process of game creation and return the value
		if (toDo != TO_CONTINUE)
			return toDo;
		do {
			Interface interface;
			Character character = SaveUtils::load(charName, interface);
			SessionController sessionController;
			toDo = sessionController.launch(character, interface);
		} while (toDo == REDO);
		return toDo;
	}
	//If you press Load game, you choose the character you want
	//And the game load it
	else if (choice == 1) {
		std::string charName = "";
		int toDo;
		do {
			LoadGameMenuController loadGameMenu;
			toDo = loadGameMenu.launch(charName);
		}
		while (toDo == REDO);
		//If toDo contains an other value than TO_CONTNIUE, we
		//Stop the process of game loading and return the value
		if (toDo != TO_CONTINUE)
			return toDo;
		do {
			Interface interface;
			Character character = SaveUtils::load(charName, interface);
			SessionController sessionController;
			toDo = sessionController.launch(character, interface);
		} while (toDo == REDO);
		return toDo;
	}
	return CLOSE_INPUT;
}