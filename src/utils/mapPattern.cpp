#include "../headers/utils/mapPattern.h"

MapPattern::MapPattern() {}

int MapPattern::flood(MapPrototype &map) {
	int fX,fY;
	int k = 0;
	//We take a random floor
	do {
		fX = rand()%map.x;
		fY = rand()%map.y;
	} while (map.cell[fX][fY] != FLOOR);
	//And we start flooding from this cell
	flood_rec(map, fX, fY);
	//Then we replace flooded cells by normal cells
	//And non flooded cells by walls
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
			if (map.cell[i][j] == FLOOR)
				map.cell[i][j] = WALL;
			else if (map.cell[i][j] == DOOR)
				map.cell[i][j] = WALL;
			else if (map.cell[i][j] == FLOOR<<4) {
				map.cell[i][j] = FLOOR;
				k++;
			}
			else if (map.cell[i][j] == DOOR<<4) {
				map.cell[i][j] = DOOR;
				k++;
			}
	return k;
}

void MapPattern::flood_rec(MapPrototype &map, int fX, int fY) {
	//We mark the cell flooded
	if (map.cell[fX][fY] == FLOOR)
		map.cell[fX][fY] = FLOOR<<4;
	if (map.cell[fX][fY] == DOOR)
		map.cell[fX][fY] = DOOR<<4;
	//We call the flood method on the adjacent cells
	if ((map.cell[fX-1][fY] == DOOR) || (map.cell[fX-1][fY] == FLOOR))
		flood_rec(map,fX-1,fY);
	if ((map.cell[fX+1][fY] == DOOR) || (map.cell[fX+1][fY] == FLOOR))
		flood_rec(map,fX+1,fY);
	if ((map.cell[fX][fY-1] == DOOR) || (map.cell[fX][fY-1] == FLOOR))
		flood_rec(map,fX,fY-1);
	if ((map.cell[fX][fY+1] == DOOR) || (map.cell[fX][fY+1] == FLOOR))
		flood_rec(map,fX,fY+1);
}

void MapPattern::cavernGenerator(MapPrototype &map, int toWall, int limit, int loop) {
	//It's a cellula automata algorithm
	//At te begining each cell is randomly convert
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
			if ((i==0)||(i==(map.x-1))||(j==0)||(j==(map.y-1)))
				map.cell[i][j] = WALL;
			else
				if ((rand()%100)<toWall)
					map.cell[i][j] = WALL;
				else
					map.cell[i][j] = FLOOR;
	//Then we apply four times a simple algorithm
	//For each cell, if the number of neighboors (include the cell itself)
	//Is in [1..4] we convert it to a wall
	int copy[map.x][map.y];
	for (int turn=0;turn<(loop+1);turn++) {
		for (int i=1;i<map.x-1;i++)
			for (int j=1;j<map.y-1;j++) {
				int count1=0;
				for (int ii=i-1;ii<i+2;ii++)
					for (int jj=j-1;jj<j+2;jj++)
						if (map.cell[ii][jj] == WALL)
							count1++;
				if ((count1 > limit) || (count1 < 1))
					copy[i][j] = WALL;
				else
					copy[i][j] = FLOOR;
			}
		//Here we copy the map, to prepare the new step of the loop
		for (int i=1;i<map.x-1;i++)
			for (int j=1;j<map.y-1;j++)
				map.cell[i][j] = copy[i][j];
	}
	//Finally we convert isolated walls to floor (3 times to make it clean)
	for (int turn=0;turn<loop;turn++) {
		for (int i=1;i<map.x-1;i++)
			for (int j=1;j<map.y-1;j++) {
				int count1=0;
				for (int ii=i-1;ii<i+2;ii++)
					for (int jj=j-1;jj<j+2;jj++)
						if (map.cell[ii][jj] == WALL)
							count1++;
				if (count1 > limit)
					copy[i][j] = WALL;
				else
					copy[i][j] = FLOOR;
			}
		for (int i=1;i<map.x-1;i++)
			for (int j=1;j<map.y-1;j++)
				map.cell[i][j] = copy[i][j];
	}
}

void MapPattern::addWalls(MapPrototype &map, int k) {
	for (int i=0;i<k;i++) {
		int rX = rand()%map.x;
		int rY = rand()%map.y;
		if (canAddWall(map, rX, rY))
			map.cell[rX][rY] = WALL_ITEM;
	}
}

bool MapPattern::canAddWall(MapPrototype &map, int x, int y) {
	if ((x <= 0) || (y <= 0))
		return false;
	if ((x >= (map.x-1)) || (y >= (map.y-1)))
		return false;
	if (map.cell[x][y] <= IS_SOLID)
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
		if (map.cell[x+displ[i][0]][y+displ[i][1]] <= IS_SOLID) {
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

Random::Random() {}

std::string Random::getRandomName() {
	return "Unknow name";
}

void Random::floorCell(Cell &cell) {
	cell.dungeonFloorA();
}

void Random::doorCell(Cell &cell) {
	cell.dungeonFloorA();
}

void Random::wallCell(Cell &cell) {
	cell.dungeonWallA();
}

void Random::wallItemCell(Cell &cell) {
	cell.dungeonWallA();
}

void Random::apply(MapPrototype &map) {
	//Cells are randomly floor of wall
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
			if (rand()%2)
				map.cell[i][j] = WALL;
			else
				map.cell[i][j] = FLOOR;
}