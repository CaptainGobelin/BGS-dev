#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <cmath>

int main(int argc, char *argv[]) {
	sf::Image blueprint;
	blueprint.loadFromFile("room_blueprint.png");
	std::ofstream file("rooms.h", std::ios::out | std::ios::trunc);
	if (!file)
		return 0;
	sf::Vector2u size = blueprint.getSize();
	std::list<std::pair<int,int> > roomSizes;
	int k = 0;
	for (unsigned int j=0;j<size.y;j++)
		for (unsigned int i=0;i<size.x;i++)
			if (blueprint.getPixel(i, j) == sf::Color(0,0,128)) {
				int x = i+1;
				int y = j+1;
				int xx, yy;
				do
					i++;
				while (blueprint.getPixel(i, j) != sf::Color(0,0,128));
				xx = i;
				int jj = j;
				do
					jj++;
				while (blueprint.getPixel(i, jj) != sf::Color(255,255,255));
				yy = jj;
				k++;
				std::cout << "Room " << k << ": " << (yy-y) << "x" << (xx-x) << std::endl;
				roomSizes.push_back(std::pair<int,int>(yy-y, xx-x));
			}
	int maxX = 0;
	int maxY = 0;
	file << "#define NB_ROOMS " << k << "\n\n";
	file << "static const int roomsSizes[" << k << "][2] = {\n";
	for (std::list<std::pair<int,int> >::iterator it=roomSizes.begin();it!=roomSizes.end();++it) {
		if (it != roomSizes.begin())
			file << ",\n";
		file << "{" << (*it).first << ", " << (*it).second << "}";
		maxX = std::max((*it).first, maxX);
		maxY = std::max((*it).second, maxY);
	}
	file << "\n};\n\n";
	std::cout << "Max: " << maxX << "x" << maxY << std::endl;
	file << "static const int rooms[" << k << "][" << maxX << "][" << maxY << "] = {\n";
	int count = 0;
	for (unsigned int j=0;j<size.y;j++)
		for (unsigned int i=0;i<size.x;i++)
			if (blueprint.getPixel(i, j) == sf::Color(0,0,128)) {
				int x = i+1;
				int y = j+1;
				int xx, yy;
				do
					i++;
				while (blueprint.getPixel(i, j) != sf::Color(0,0,128));
				xx = i;
				int jj = j;
				do
					jj++;
				while (blueprint.getPixel(i, jj) != sf::Color(255,255,255));
				yy = jj;
				count++;
				if (count != 1)
					file << ",\n";
				file << "{\n";
				for (int n=y;n<yy;n++) {
					if (n != y)
						file << ",\n";
					file << "{";
					for (int m=x;m<xx;m++) {
						if (m != x)
							file << ",";
						if (blueprint.getPixel(m,n) == sf::Color(255, 0, 0))
							file << "WALL";
						else if (blueprint.getPixel(m,n) == sf::Color(0, 255, 0))
							file << "DOOR";
						else
							file << "FLOOR";
					}
					file << "}";
				}
				file << "\n}";
			}
	file << "\n};";
	return 0;
}
