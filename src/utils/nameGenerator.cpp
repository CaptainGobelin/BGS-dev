#include "../headers/utils/nameGenerator.h"

std::string NameGenerator::humanName() {
	//Name generation algorithm use the markov chains
	//We analyze names (look at utils/name_analyze) to construct markov chains
	//Then we use this "tableau" to construct a random name
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

std::string NameGenerator::dungeonName() {
	std::string result = "The ";
	result += (getAdjectif()+"Dungeon of "+getName());
	return result;
}

std::string NameGenerator::getAdjectif() {
	std::string result = "";
	int n = rand()%10;
	switch (n) {
		case 0:
			result += "Secret ";
			break;
		case 1:
			result += "Deadly ";
			break;
		case 2:
			result += "Magic ";
			break;
		case 3:
			result += "Dark ";
			break;
		case 4:
			result += "Old ";
			break;
	}
	return result;
}

std::string NameGenerator::getName() {
	std::string result = "";
	int n = rand()%12;
	switch (n) {
		case 0:
			result += "the "+getAdjectifName()+"King";
			break;
		case 1:
			result += "the "+getAdjectifName()+"Wizard";
			break;
		case 2:
			result += "Lord "+humanName();
			break;
		case 3:
			result += humanName()+" the Lich";
			break;
		case 4:
			result += humanName()+" the Warlock";
			break;
		case 5:
			result += humanName()+" the Vampire";
			break;
		case 6:
			result += humanName()+" the Warlord";
			break;
		default:
			result += humanName();
	}
	return result;
}

std::string NameGenerator::getAdjectifName() {
	std::string result = "";
	int n = rand()%4;
	switch (n) {
		case 0:
			result += "Mad ";
			break;
		case 1:
			result += "Lost ";
			break;
		case 2:
			result += "Dark ";
			break;
		case 3:
			result += "Dead ";
			break;
	}
	return result;
}