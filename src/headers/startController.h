#ifndef CSTART_H
#define CSTART_H

#include "utils/lib.h"
#include "utils/const.h"

#include "GUI/startScreen.h"

class StartController {
	public :
		StartController();
		int launch();
	private :
		StartScreen startScreen;
};

#endif
