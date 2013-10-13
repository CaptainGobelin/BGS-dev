#include "nameGenerator.h"

NameGenerator::NameGenerator() {}

std::string NameGenerator::generate() {
	std::string result = "";
	bool stop = false;
	int ascii = 0;
	while (!stop) {
		if (rand()%100 < 20)
			stop = true;
		float r = (rand()%100001)/100000.f;
		for (int i=1;i<27;i++)
			if (tableau[ascii][i] >= r) {
				result += (i+96);
				if (result.size() > 2)
					if (result[result.size()-1] == result[result.size()-3]) {
						result = "";
						ascii = 0;
					}
					else
						ascii = i;
				else
					ascii = i;
				break;
			}
			else if (i == 26) {
				result = "";
				ascii = 0;
			}
		if (stop)
			if (result.size() < 4)
				stop = false;
			if (result.size() > 8) {
				result = "";
				ascii = 0;
				stop = false;
			}
	}
	result[0] -= 32;
	return result;
}