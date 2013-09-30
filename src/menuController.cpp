#include "headers/menuController.h"

MenuController::MenuController() {}

int MenuController::launch() {
	LoadGameMenuController loadGameMenu;
	Interface interface;
	std::string charName = "";
	loadGameMenu.launch(&charName);
	//Character c("Teljin", HUMAN_CODE, "D1");
	//SaveUtils::save(c);
	Character character = SaveUtils::load(charName, interface);
	SessionController sessionController;
	return sessionController.launch(character, interface);
}