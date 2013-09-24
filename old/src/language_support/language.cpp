#include "../headers/Model/language.h"

void Language::changeLanguage(OptionsFile opt) {
	if (opt.getLanguage() == "en")
		lang = 0;
	else if (opt.getLanguage() == "fr")
		lang = 1;
	else lang = 0;
}
