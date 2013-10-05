#include "headers/sessionController.h"

SessionController::SessionController() {}

int SessionController::launch(Character &character, Interface &interface) {
	//Initialization
	//Map map = SaveUtils::loadMap(character.getName(), character.getMap());
	Map map = MapGenerator::generate(20,20, new Dungeon());
	SessionScreen sessionScreen;
	character.checkView(map);
	sessionScreen.display(character, interface, map);
	GameInput input;
	//Game Loop
	while (input.getValue() != CLOSE_INPUT) {
		//To know if we have to count the current turn.
		bool played = false;
		//To know if we have to refresh the screen.
		bool toRefresh = true;
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
				played = true;
				break;
			}
			case DOWN_INPUT : {
				if (character.move(0,1,map))
					interface.showItems(map.cell[character.getX()][character.getY()]);
				played = true;
				break;
			}
			case RIGHT_INPUT : {
				if (character.move(1,0,map))
					interface.showItems(map.cell[character.getX()][character.getY()]);
				played = true;
				break;
			}
			case LEFT_INPUT : {
				if (character.move(-1,0,map))
					interface.showItems(map.cell[character.getX()][character.getY()]);
				played = true;
				break;
			}
			default:
				toRefresh = false;
		}
		if (played) {
			map.refreshCells(character.getX(), character.getY());
			character.checkView(map);
		}
		if (toRefresh)
			sessionScreen.display(character, interface, map);
	}
	SaveUtils::save(character, interface);
	//SaveUtils::saveMap(character.getName(), character.getMap(), map);
	return CLOSE_INPUT;
}