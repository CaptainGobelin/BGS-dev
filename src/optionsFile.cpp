#include "headers/optionsFile.h"

bool OptionsFile::load() {
	std::string line;
	std::ifstream file(OPTION_PATH, std::ios::in);
	if (file) {
		std::string line;
        while (getline(file, line))
        	setOption(line);
        return true;
	}
	else
		return false;
}

void OptionsFile::setOption(std::string line) {
	if (line.substr(0,2) == "%%")
		return;
	int pos = line.find("=");
	std::string value = line.substr(pos+1,line.size()-pos);
	if (line.substr(0,pos) == "frameLimit") {
		frameLimit = std::atoi(value.c_str());
    }
    else if (line.substr(0,pos) == "vSync") {
    	vSync = toBool(value);
    }
    else if (line.substr(0,pos) == "map") {
    	mapGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "inventory") {
    	inventoryGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "upMove") {
    	upGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "downMove") {
    	downGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "rightMove") {
    	rightGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "leftMove") {
    	leftGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "menu") {
    	menuGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "validation") {
    	validGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "exit") {
    	exitGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "confirm") {
    	confirmGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "cancel") {
    	cancelGameKey = toKey(value);
    }
    else if (line.substr(0,pos) == "pick") {
    	pickGameKey = toKey(value);
    }
}

sf::Keyboard::Key OptionsFile::toKey(std::string const& s) {
	if (s == "A")
		return sf::Keyboard::A;
	if (s == "B")
		return sf::Keyboard::B;
	if (s == "C")
		return sf::Keyboard::C;
	if (s == "D")
		return sf::Keyboard::D;
	if (s == "E")
		return sf::Keyboard::E;
	if (s == "F")
		return sf::Keyboard::F;
	if (s == "G")
		return sf::Keyboard::G;
	if (s == "H")
		return sf::Keyboard::H;
	if (s == "I")
		return sf::Keyboard::I;
	if (s == "J")
		return sf::Keyboard::J;
	if (s == "K")
		return sf::Keyboard::K;
	if (s == "L")
		return sf::Keyboard::L;
	if (s == "M")
		return sf::Keyboard::M;
	if (s == "N")
		return sf::Keyboard::N;
	if (s == "O")
		return sf::Keyboard::O;
	if (s == "P")
		return sf::Keyboard::P;
	if (s == "Q")
		return sf::Keyboard::Q;
	if (s == "R")
		return sf::Keyboard::R;
	if (s == "S")
		return sf::Keyboard::S;
	if (s == "T")
		return sf::Keyboard::T;
	if (s == "U")
		return sf::Keyboard::U;
	if (s == "V")
		return sf::Keyboard::V;
	if (s == "W")
		return sf::Keyboard::W;
	if (s == "X")
		return sf::Keyboard::X;
	if (s == "Y")
		return sf::Keyboard::Y;
	if (s == "Z")
		return sf::Keyboard::Z;
	if (s == "UpArrow")
		return sf::Keyboard::Up;
	if (s == "DownArrow")
		return sf::Keyboard::Down;
	if (s == "RightArrow")
		return sf::Keyboard::Right;
	if (s == "LeftArrow")
		return sf::Keyboard::Left;
	if (s == "Return")
		return sf::Keyboard::Return;
	if (s == "Backspace")
		return sf::Keyboard::BackSpace;
	if (s == "Escape")
		return sf::Keyboard::Escape;
}

bool OptionsFile::toBool(std::string const& s) {
     return s == "true";
}
