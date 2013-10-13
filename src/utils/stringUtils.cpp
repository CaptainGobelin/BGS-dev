#include "../headers/utils/stringUtils.h"

std::string StringUtils::saveStem(std::string s) {
	std::string result = "";
	for (int i=0;i<s.size();i++) {
		if (s.compare(i,1," ") != 0)
			result += s[i];
	}
	return result;
}

int StringUtils::getMapCode(std::string mapCode, int component) {
	int count = 0;
	//Skip the previous component
	for (int i=0;i<(component-1);i++) {
		while (mapCode.compare(count,1,"_") != 0)
			count++;
		count++;
	}
	std::string resultS = "";
	//Stock the component we need
	while ((mapCode.compare(count,1,"_") != 0) && (count < mapCode.size())) {
		resultS += mapCode[count];
		count++;
	}
	//Integer conversion
	return std::atoi(const_cast<char*>(resultS.c_str()));
}