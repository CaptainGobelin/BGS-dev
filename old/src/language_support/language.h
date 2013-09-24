#ifndef LANG_H
#define LANG_H

#include "../utils/lib.h"
#include "../utils/const.h"

#include "../optionsFile.h"

class Language {
	public :
		static int lang;
		static std::wstring menuTexts[1][2];
		static void changeLanguage(OptionsFile opt);
};

#endif
