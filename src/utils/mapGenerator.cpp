#include "../headers/utils/mapGenerator.h"

extern sf::RenderWindow window;
extern sf::View view;

Map MapGenerator::generate(int x, int y, MapPattern *pattern, std::string mapCode) {
	//Initialization
	int l = rand() % x + x;
	int w = rand() % y + y;
	Map map(l+2,w+2);
	MapPrototype mapP(l,w);
	//We generate a prototype of the new map
	pattern->apply(mapP);
	//Then we convert the prototype into a real map
	for (int i=0;i<l;i++)
		for (int j=0;j<w;j++) {
			if (mapP.cell[i][j] == 1)
				pattern->wallCell(map.cell[i+1][j+1]);
			else
				pattern->floorCell(map.cell[i+1][j+1]);
		}
	map.setName(pattern->getRandomName());
	//We generate exits (entrance are only generate when we need one)
	int xE,yE;
	do {
		xE = rand()%l;
		yE = rand()%w;
	} while (map.cell[xE][yE].isSolid());
	map.cell[xE][yE].dungeonExit();
	//And finally we generate code for linked map
	int newMapCode = StringUtils::getMapCode(mapCode, 1);
	std::ostringstream oss;
	oss.str("");
	oss << (newMapCode+1);
	newMapCode = StringUtils::getMapCode(mapCode, 2);
	oss << "_" << (newMapCode);
	newMapCode = StringUtils::getMapCode(mapCode, 3);
	oss << "_" << (newMapCode+1);
	map.cell[xE][yE].exits.push_front(MapExit(oss.str()));
	return map;
}