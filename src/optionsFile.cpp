#include "headers/optionsFile.h"

OptionsFile::OptionsFile() {
	this->frameLimit = 50;
	this->vSync = true;
}

bool OptionsFile::load() {
	std::string line;
	std::ifstream file(OPTION_PATH, std::ios::in);
	if (file) {
		file >> line;
		if (line == "/*") {
			while (line != "*/")
				file >> line;
			file >> line;
		}
		file >> line;
		this->frameLimit = std::atoi(line.c_str());
		file >> line;
		file >> line;
		this->vSync = toBool(line);
		file.close();
		return true;
	}
	else
		return false;
}

bool OptionsFile::toBool(std::string const& s) {
     return s == "true";
}
