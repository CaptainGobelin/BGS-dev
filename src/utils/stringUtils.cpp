#include "../headers/utils/stringUtils.h"

std::string StringUtils::saveStem(std::string s) {
	std::string result = "";
	for (int i=0;i<s.size();i++) {
		if (s.compare(i,1," ") != 0)
			result += s[i];
	}
	return result;
}