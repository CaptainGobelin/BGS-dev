#include "mapGenUtils.h"

bool MapGenUtils::canAddWall(Map &map, int x, int y) {
	if ((x <= 0) || (y <= 0))
		return false;
	if ((x >= (map.x-1)) || (y >= (map.y-1)))
		return false;
	if (map.cell[x][y] == 1)
		return false;
	int result = 0;
	bool wallMemory = false;
	int displ[8][2] = {
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{0, 1},
		{1, 1},
		{1, 0},
		{1, -1},
		{0, -1}
	};
	for (int i=0;i<8;i++)
		if (map.cell[x+displ[i][0]][y+displ[i][1]] == 1) {
			if (!wallMemory) {
				result++;
				wallMemory = true;
			}
		}
		else
			wallMemory = false;
	if (result < 2)
		return true;
	return false;
}