#include "headers/startController.h"

StartController::StartController() {
	startScreen.display();
}

int StartController::launch() {
	startScreen.display();
	//Get the input value and act accordingly
	GameInput input = this->startScreen.recupInput();
	if (input.getValue() == CLOSE_INPUT)
		return input.getValue();
	return TO_MAIN_MENU;
}
