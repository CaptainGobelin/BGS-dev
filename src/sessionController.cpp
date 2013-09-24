#include "headers/sessionController.h"

SessionController::SessionController() {}

int SessionController::launch(Character &character, Interface &interface) {
	//Initialization
	Map map = SaveUtils::loadMap(character.getName(), character.getMap());
	SessionScreen sessionScreen;
	character.checkView(map);
	sessionScreen.display(character, interface, map);
	GameInput input;
	//Game Loop
	while (input.getValue() != CLOSE_INPUT) {
		map.refreshCells(character.getX(), character.getY());
		input = sessionScreen.recupInput();
		switch (input.getValue()) {
			case M_INPUT : {
				MapController mapController(map, character);
				input.setValue(mapController.launch(map, character));
				break;
			}
			case UP_INPUT : {
				if (character.move(0,-1,map))
					interface.showItems(map.cell[character.getX()][character.getY()]);
				break;
			}
			case DOWN_INPUT : {
				if (character.move(0,1,map))
					interface.showItems(map.cell[character.getX()][character.getY()]);
				break;
			}
			case RIGHT_INPUT : {
				if (character.move(1,0,map))
					interface.showItems(map.cell[character.getX()][character.getY()]);
				break;
			}
			case LEFT_INPUT : {
				if (character.move(-1,0,map))
					interface.showItems(map.cell[character.getX()][character.getY()]);
				break;
			}
		}
		character.checkView(map);
		sessionScreen.display(character, interface, map);
	}
	return CLOSE_INPUT;
}