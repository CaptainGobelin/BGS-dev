#ifndef OPTIONS_H
#define OPTIONS_H

#include "utils/const.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

class OptionsFile {
	public:
		OptionsFile();
		const int &getFrameLimit() const {return frameLimit;}
		void setFrameLimit(const int &newFrameLimit) {frameLimit=newFrameLimit;}
		const bool &getVSync() const {return vSync;}
		void setVSync(const bool &newVSync) {vSync=newVSync;}

		bool load();
		
	private:
		int frameLimit;
		bool vSync;

		bool toBool(std::string const& s);
};

#endif
