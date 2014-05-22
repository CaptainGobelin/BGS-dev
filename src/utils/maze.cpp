#include "../headers/utils/maze.h"

Maze::Maze() {}

void Maze::apply(MapPrototype &map) {
	//Maze generation is simple, it's a backtracking algorithm
	//Which generate perfect maze
	//First, all odd cells are floors
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
			if ((i==0)||(j==0)||(i==(map.x-1))||(j==(map.y-1)))
				map.cell[i][j] = WALL;
			else {
				if ((i%2) && (j%2))
					map.cell[i][j] = FLOOR<<4;
				else
					map.cell[i][j] = WALL;
			}
	//Then we generate the perfect maze
	apply_backtrack(map, 1, 1);
	//And we remove dead ends (cause dead ends are not funny !)
	remove_dead_end(map);
}

std::string Maze::getRandomName() {
	return "Unknow name";
}

void Maze::floorCell(Cell &cell) {
	cell.dungeonFloorA();
}

void Maze::doorCell(Cell &cell) {
	cell.dungeonFloorA();
}

void Maze::wallCell(Cell &cell) {
	cell.dungeonWallA();
}

void Maze::wallItemCell(Cell &cell) {
	cell.dungeonWallA();
}

void Maze::apply_backtrack(MapPrototype &map, int cX, int cY) {
	//Backtrack method is a bit long but simple
	//We try to construct a way with random directions
	//When we are blocked, we try another direction
	map.cell[cX][cY] = FLOOR;
	int turn = rand()%4;
	for (int k=0;k<4;k++) {
		switch (turn) {
			case 0: {
				if (cX != 1)
					if (map.cell[cX-2][cY] == FLOOR<<4) {
						map.cell[cX-1][cY] = FLOOR;
						apply_backtrack(map, cX-2, cY);
					}
				break;
			}
			case 1: {
				if (cY < (map.y-2))
					if (map.cell[cX][cY+2] == FLOOR<<4) {
						map.cell[cX][cY+1] = FLOOR;
						apply_backtrack(map, cX, cY+2);
					}
				break;
			}
			case 2: {
				if (cX < (map.x-2))
					if (map.cell[cX+2][cY] == FLOOR<<4) {
						map.cell[cX+1][cY] = FLOOR;
						apply_backtrack(map, cX+2, cY);
					}
				break;
			}
			case 3: {
				if (cY != 1)
					if (map.cell[cX][cY-2] == FLOOR<<4) {
						map.cell[cX][cY-1] = FLOOR;
						apply_backtrack(map, cX, cY-2);
					}
				break;
			}
		}
		turn = (turn+1)%4;
	}
}

void Maze::remove_dead_end(MapPrototype &map) {
	//To remove dead ends, we just look all the cells
	//If there's a dead ends, we add a way to a random direction
	for (int i=1;i<(map.x-1);i+=2)
		for (int j=1;j<(map.y-1);j+=2)
			if (is_dead_end(map,i,j)) {
				int dir = rand()%4;
				for (int k=0;k<4;k++) {
					switch (dir) {
						case 0:
							if ((i != 1) && (map.cell[i-1][j] == WALL)) {
								map.cell[i-1][j] = FLOOR;
								k = 4;
							}
							break;
						case 1:
							if ((i < (map.x-2-!(map.x%2))) && (map.cell[i+1][j] == WALL)) {
								map.cell[i+1][j] = FLOOR;
								k = 4;
							}
							break;
						case 2:
							if ((j != 1) && (map.cell[i][j-1] == WALL)) {
								map.cell[i][j-1] = FLOOR;
								k = 4;
							}
							break;
						case 3:
							if ((j < (map.y-2-!(map.y%2))) && (map.cell[i][j+1] == WALL)) {
								map.cell[i][j+1] = FLOOR;
								k = 4;
							}
							break;
					}
					dir = (dir+1)%4;
				}
			}
}

bool Maze::is_dead_end(MapPrototype &map, int i, int j) {
	//A dead end is a cell with just one adjacent floor
	int count = 0;
	if (map.cell[i-1][j] == WALL)
		count++;
	if (map.cell[i+1][j] == WALL)
		count++;
	if (map.cell[i][j-1] == WALL)
		count++;
	if (map.cell[i][j+1] == WALL)
		count++;
	if (count > 2)
		return true;
	return false;
}