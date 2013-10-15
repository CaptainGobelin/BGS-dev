#include "../headers/Model/interface.h"

Interface::Interface() {
	this->panel.setTexture(Textures::texturesInterface);
	this->panel.setPosition(L_WINDOW-320,0);
	this->font.loadFromFile((std::string)FONT_PATH+"pcsenior.ttf");
	for (int i=0;i<MESS_LINES;i++) {
		this->textBox[i].setFont(font);
		this->textBox[i].setCharacterSize(9);
		this->textBox[i].setColor(sf::Color::Black);
		this->textBox[i].setPosition(L_WINDOW-300, H_WINDOW-30-MESS_LINES*MESS_SPACE+(i*MESS_SPACE));
		this->textBox[i].setString("");
	}
}

const std::string Interface::getMessage(int i) const {
	if ((i < 0)||(i>=MESS_LINES)) 
		return "";
	else 
		return textBox[i].getString();
}

void Interface::write(std::string message) {
	//If the message is too long for one line, cut in two
	if (message.length() > 31) {
		int cut = 31;
		while (message.at(cut) != ' ')
			cut --;
		for (int i=0;i<MESS_LINES-1;i++)
			this->textBox[i].setString(textBox[i+1].getString());
		this->textBox[MESS_LINES-1].setString(message.substr(0,cut));
		write(message.substr(cut+1,message.length()));
	}
	 else {
		for (int i=0;i<MESS_LINES-1;i++)
			this->textBox[i].setString(textBox[i+1].getString());
		this->textBox[MESS_LINES-1].setString(message);
	}
}

void Interface::draw() {
	GameWindow::window.setView(GameWindow::viewInt);
	GameWindow::window.draw(this->panel);
	for (int i=0;i<MESS_LINES;i++)
		GameWindow::window.draw(this->textBox[i]);
}

void Interface::showItems(Cell &cell) {
	//Just construct a message of the list of items
	if (cell.drops.empty())
		return;
	std::ostringstream oss;
	std::string line = "You see";
	int count = 1;
	for (std::list<Item>::iterator it=cell.drops.begin(); it != cell.drops.end(); ++it) {
		oss.str("");
		oss << count;
		if (count == 1)
			line += " (" + oss.str()+") "+(*it).getName();
		else if (it == --(cell.drops.end()))
			line += " and (" + oss.str()+") "+(*it).getName();
		else
			line += ", (" + oss.str()+") "+(*it).getName();
		count++;
	}
	line += ".";
	write(line);
}

void Interface::showDestination(Cell &cell) {
	if (cell.exits.empty())
		return;
	std::string line = "You see a way to ";
	line += cell.exits.begin()->getDestName();
	line += ".";
	write(line);
}