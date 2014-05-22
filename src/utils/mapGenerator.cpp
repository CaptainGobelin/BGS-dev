#include "../headers/utils/mapGenerator.h"

extern sf::RenderWindow window;
extern sf::View view;

Map MapGenerator::generate(int x, int y, MapPattern *pattern, std::string mapCode, int dependencies) {
	//Initialization
	int l = rand() % x + x;
	int w = rand() % y + y;
	Map map(l+2,w+2);
	map.setDependencies(dependencies);
	MapPrototype mapP(l,w);
	//We generate a prototype of the new map
	pattern->apply(mapP);
	pattern->addWalls(mapP, 30);
	//Then we convert the prototype into a real map
	for (int i=0;i<l;i++)
		for (int j=0;j<w;j++) {
			if (mapP.cell[i][j] == WALL)
				pattern->wallCell(map.cell[i+1][j+1]);
			else if (mapP.cell[i][j] == FLOOR)
				pattern->floorCell(map.cell[i+1][j+1]);
			else if (mapP.cell[i][j] == DOOR)
				pattern->doorCell(map.cell[i+1][j+1]);
			else if (mapP.cell[i][j] == WALL_ITEM)
				pattern->wallItemCell(map.cell[i+1][j+1]);
		}
	map.setName(pattern->getRandomName());
	//If the map is a leaf we don't need to create way to oter map
	if (dependencies <= 0)
		return map;
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
	oss << newMapCode;
	newMapCode = StringUtils::getMapCode(mapCode, 2);
	oss << "_" << 1;
	newMapCode = StringUtils::getMapCode(mapCode, 3);
	oss << "_" << newMapCode+1;
	map.cell[xE][yE].exits.push_front(MapExit(oss.str(), dependencies-1));
	return map;
}