#include "../headers/GUI/loadGameMenuScreen.h"

LoadGameMenuScreen::LoadGameMenuScreen() {
	font.loadFromFile((std::string)FONT_PATH+"pcsenior.ttf");
	int count = 0;
	boost::filesystem::path path(SAVE_PATH);
	for(boost::filesystem::directory_iterator it(path);it!=boost::filesystem::directory_iterator();++it)
		if(boost::filesystem::extension(*it) == ".sav") {
			Interface i;
			Character c = SaveUtils::load((*it).path().stem().string(),i);
			std::string s = c.getName();
			/*if (c.getRace().getRaceCode() == HUMAN_CODE)
				s += ", Human";
			else
				s += ", Unknow";*/
			characters.push_front(sf::Text(s,font,20));
			count++;
		}
}

int LoadGameMenuScreen::getNChoices() {
	return characters.size();
}

std::string LoadGameMenuScreen::getName(int choice) {
	int count = 0;
	for (std::list<sf::Text>::iterator it=characters.begin();it!=characters.end();++it) {
		if (count == choice)
			return (*it).getString();
		count++;
	}
	return characters.begin()->getString();
}

GameInput LoadGameMenuScreen::recupInput() {
	sf::Event event;
	GameInput input;
	while (!input.isValid()) {
		GameWindow::window.waitEvent(event);
		input.treatEvent(event);
	}
	return input;
}

void LoadGameMenuScreen::display(int choice) {
	int count = 0;
	for (std::list<sf::Text>::iterator it=characters.begin();it!=characters.end();++it) {
		(*it).setPosition(10, 10 + count*30);
		if (count == choice)
			(*it).setColor(sf::Color::Blue);
		else
			(*it).setColor(sf::Color::White);
		GameWindow::window.draw(*it);
		count++;
	}
	GameWindow::window.display();
}