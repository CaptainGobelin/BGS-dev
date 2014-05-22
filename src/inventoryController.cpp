#include "headers/inventoryController.h"

InventoryController::InventoryController() {}

int InventoryController::launch(Character &character) {
	//Juste display the inventory until you press I, Escape or Close
	inventoryScreen.display(character);
	GameInput input = this->inventoryScreen.recupInput();
	while (input.getValue() != I_INPUT) {
		if (input.getValue() == ESCAPE_INPUT)
			return I_INPUT;
		if (input.getValue() == CLOSE_INPUT)
			return input.getValue();
		input = this->inventoryScreen.recupInput();
	}
	return input.getValue();
}