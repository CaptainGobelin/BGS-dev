#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

int main(int argc, char *argv[]) {
	float proba[27][27];
	for (int i=0;i<27;i++)
		for (int j=0;j<27;j++)
			proba[i][j] = 0;
	int numb[27] = {0};
	std::string line;
	std::ifstream file("human_names.txt", std::ios::in);
	if (file) {
		while (std::getline(file, line)) {
			numb[0]++;
			int asciiP = 0;
			for (unsigned int i=0;i<line.size();i++) {
				int ascii = line[i];
				if (ascii < 97)
					ascii += 32;
				ascii -= 96;
				if (i != line.size()-1)
					numb[ascii]++;
				proba[asciiP][ascii]++;
				asciiP = ascii;
			}
		}
		file.close();
	}
	std::ofstream file2("human_analyze.h", std::ios::out | std::ios::trunc);
	for (int i=0;i<27;i++)
		for (int j=0;j<27;j++)
			if (numb[i] != 0)
				proba[i][j] /= numb[i];
	for (int i=0;i<27;i++)
		for (int j=0;j<27;j++) {
			if (j > 0)
				proba[i][j] += proba[i][j-1];
		}
	if (file2) {
		file2 << "static const float tableau[27][27] = {\n";
		for (int i=0;i<27;i++) {
			if (i > 0)
				file2 << ",";
			file2 << "{";
			for (int j=0;j<27;j++) {
				if (j > 0)
					file2 << ",";
				file2 << proba[i][j];
			}
			file2 << "}\n";
		}
		file2 << "};";
		file2.close();
	}
	return 0;
}
