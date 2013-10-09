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
		//To know if we have to count the current turn.
		bool played = false;
		//To know if we have to refresh the screen.
		bool toRefresh = true;
		//To know if the player have changed his position.
		bool moved = false;
		input = sessionScreen.recupInput();
		switch (input.getValue()) {
			moved = false;
			case M_INPUT : {
				MapController mapController(map, character);
				input.setValue(mapController.launch(map, character));
				break;
			}
			case Q_INPUT : {
				if (changeMap(character, map, interface)) {
					SaveUtils::save(character, interface);
					return REDO;
				}
				else
					interface.write("You cannot exit from here !");
				break;
			}
			case UP_INPUT : {
				moved = character.move(0,-1,map);
				played = true;
				break;
			}
			case DOWN_INPUT : {
				moved = character.move(0,1,map);
				played = true;
				break;
			}
			case RIGHT_INPUT : {
				moved = character.move(1,0,map);
				played = true;
				break;
			}
			case LEFT_INPUT : {
				moved = character.move(-1,0,map);
				played = true;
				break;
			}
			default:
				toRefresh = false;
		}
		if (moved) {
			interface.showItems(map.cell[character.getX()][character.getY()]);
			interface.showDestination(map.cell[character.getX()][character.getY()]);
		}
		if (played) {
			map.refreshCells(character.getX(), character.getY());
			character.checkView(map);
		}
		if (toRefresh)
			sessionScreen.display(character, interface, map);
	}
	SaveUtils::save(character, interface);
	SaveUtils::saveMap(character.getName(), character.getMap(), map);
	return CLOSE_INPUT;
}

bool SessionController::changeMap(Character &character, Map &map, Interface &interface) {
	if (map.cell[character.getX()][character.getY()].exits.empty())
		return false;
	SaveUtils::saveMap(character.getName(), character.getMap(), map);
	std::string dest = map.cell[character.getX()][character.getY()].exits.begin()->getDestCode();
	boost::filesystem::path path(WORLD_PATH+StringUtils::saveStem(character.getName()));
	for(boost::filesystem::directory_iterator it(path);it!=boost::filesystem::directory_iterator();++it)
		if(boost::filesystem::extension(*it) == ".map") {
			if (dest.compare((*it).path().stem().string()) == 0) {
				Map nMap = SaveUtils::loadMap(character.getName(), dest);
				map.cell[character.getX()][character.getY()].exits.begin()->setDestName(nMap.getName());
				character.goToStart(nMap, map.getName());
				character.setMap(dest);
				SaveUtils::saveMap(character.getName(), character.getMap(), nMap);
				return true;
			}
		}
	Map nMap = MapGenerator::generate(20,20, new Dungeon());
	map.cell[character.getX()][character.getY()].exits.begin()->setDestName(nMap.getName());
	character.goToStart(nMap, map.getName());
	character.setMap(dest);
	SaveUtils::saveMap(character.getName(), character.getMap(), nMap);
	interface.write("Welcome to "+nMap.getName()+".");
	return true;
}