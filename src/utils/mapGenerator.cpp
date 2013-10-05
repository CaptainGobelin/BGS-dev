#include "../headers/utils/mapGenerator.h"

extern sf::RenderWindow window;
extern sf::View view;

Map MapGenerator::generate(int x, int y, MapPattern *pattern) {
	int l = rand() % x + x;
	int w = rand() % y + y;
	Map map(l+2,w+2);
	MapPrototype mapP(l,w);
	pattern->apply(mapP);
	for (int i=0;i<l;i++)
		for (int j=0;j<w;j++) {
			if (mapP.cell[i][j] == 1)
				map.cell[i+1][j+1].dungeonWallA();
			else
				map.cell[i+1][j+1].dungeonFloorA();
		}
	return map;
}