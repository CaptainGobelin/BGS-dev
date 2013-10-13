#include "headers/newGameMenuController.h"

NewGameMenuController::NewGameMenuController() {
	boost::filesystem::path path(SAVE_PATH);
	for(boost::filesystem::directory_iterator it(path);it!=boost::filesystem::directory_iterator();++it)
		if(boost::filesystem::extension(*it) == ".sav") {
			Interface i;
			Character c = SaveUtils::load((*it).path().stem().string(),i);
			std::string s = c.getName();
			characters.push_front(StringUtils::saveStem(s));
		}
}

int NewGameMenuController::launch(std::string &name) {
	newGameMenuScreen.display(true);
	bool correct = false;
	bool stop = false;
	do {
		sf::Event event = newGameMenuScreen.recupInput();
		if (event.type == sf::Event::Closed)
			return CLOSE_INPUT;
		if (event.type == sf::Event::TextEntered) {
			sf::String s = newGameMenuScreen.characterName.getString();
			if (event.text.unicode == 8) {
				if (s.getSize() > 0)
					s.erase(s.getSize() - 1);
			}
			else if ((event.text.unicode > 96) && (event.text.unicode < 123)) {
				if (s.getSize() < 17)
					s.insert(s.getSize(), event.text.unicode);
			}
			else if ((event.text.unicode > 64) && (event.text.unicode < 91)) {
				if (s.getSize() < 17)
					s.insert(s.getSize(), event.text.unicode);
			}
			else if (event.text.unicode == 45) {
				if (s.getSize() < 17)
					s.insert(s.getSize(), event.text.unicode);
			}
			else if (event.text.unicode == 32) {
				if ((s.getSize() < 17) && ((s.getSize() > 0)))
					s.insert(s.getSize(), event.text.unicode);
			}
			correct = true;
			if (s.getSize() <= 0)
				correct = false;
			for (std::list<std::string>::iterator it=characters.begin();it!=characters.end(); ++it)
				if ((*it).compare(StringUtils::saveStem(s)) == 0)
					correct = false;
			newGameMenuScreen.characterName.setString(s);
			newGameMenuScreen.display(correct);
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape)
				return TO_MAIN_MENU;
			if (event.key.code == sf::Keyboard::Return)
				stop = correct;
		}
	} while (!stop);
	name = newGameMenuScreen.characterName.getString();
	createCharacter(name);
	return TO_CONTINUE;
}

void NewGameMenuController::createCharacter(std::string name) {
	Map map = MapGenerator::generate(20,20, new Dungeon(), "1_1_1");
	int x, y;
	do  {
		x = rand()%map.getLength();
		y = rand()%map.getWidth();
	} while (map.cell[x][y].isSolid());
	Character character(name, HUMAN_CODE, "1_1_1");
	character.setX(x);
	character.setY(y);
	Interface interface;
	SaveUtils::save(character, interface);
	std::string s = "/"+StringUtils::saveStem(name);
	s = WORLD_PATH + s;
	boost::filesystem::path path(s);
	boost::filesystem::create_directory(path);
	SaveUtils::saveMap(character.getName(), character.getMap(), map);
}