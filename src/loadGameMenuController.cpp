#include "headers/loadGameMenuController.h"

LoadGameMenuController::LoadGameMenuController() {}

int LoadGameMenuController::launch(std::string &charName) {
	int nChoices = loadGameMenuScreen.getNChoices();
	int choice = 0;
	bool stop = true;
	loadGameMenuScreen.display(choice);
	GameInput input;
	do {
		input = loadGameMenuScreen.recupInput();
		switch (input.getValue()) {
			case CLOSE_INPUT:
				return CLOSE_INPUT;
			case UP_INPUT:
				choice--;
				while (choice < 0)
					choice += nChoices;
				loadGameMenuScreen.display(choice);
				break;
			case DOWN_INPUT:
				choice = (choice+1)%nChoices;
				loadGameMenuScreen.display(choice);
				break;
			case ENTER_INPUT:
				stop = false;
				charName = loadGameMenuScreen.getName(choice);
				break;
		}
	} while (stop);
	return TO_CONTINUE;
}