#include "headers/mapController.h"

MapController::MapController(Map &map, Character &character) {
	this->mapScreen.setScale(map.getLength(), map.getWidth());
}

int MapController::launch(Map &map, Character &character) {
	mapScreen.display(map, character);
	GameInput input = this->mapScreen.recupInput();
	while (input.getValue() != M_INPUT) {
		if (input.getValue() == CLOSE_INPUT)
			return input.getValue();
		input = this->mapScreen.recupInput();
	}
	return input.getValue();
}