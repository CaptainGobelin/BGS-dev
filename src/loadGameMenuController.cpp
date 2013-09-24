#include "headers/loadGameMenuController.h"

LoadGameMenuController::LoadGameMenuController() {}

int LoadGameMenuController::launch(std::string *charName) {
	*charName = "Teljin";
	return CLOSE_INPUT;
}