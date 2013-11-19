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

Cavern::Cavern() {}

void Cavern::apply(MapPrototype &map) {
	//We make sure that the cavern has enough floors
	//In the other case we drop off the present one
	//And we generate an another cavern
	do
		cavernGenerator(map, 45, 4, 3);
	while (flood(map) < (map.x*map.y)/3);
}

std::string Cavern::getRandomName() {
	return "Unknow name";
}

void Cavern::floorCell(Cell &cell) {
	cell.cavernFloorA();
}

void Cavern::wallCell(Cell &cell) {
	cell.cavernWallA();
}

void Cavern::wallItemCell(Cell &cell) {
	cell.dungeonWallA();
}

Plain::Plain() {}

void Plain::apply(MapPrototype &map) {
	do
		cavernGenerator(map, 55, 5, 3);
	while (flood(map) < (map.x*map.y)/3);
}

std::string Plain::getRandomName() {
	return "Unknow name";
}

void Plain::floorCell(Cell &cell) {
	cell.grassA();
}

void Plain::wallCell(Cell &cell) {
	cell.treeA();
}

void Plain::wallItemCell(Cell &cell) {
	cell.treeA();
}

Labyrinth::Labyrinth() {}

void Labyrinth::apply(MapPrototype &map) {
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

std::string Labyrinth::getRandomName() {
	return "Unknow name";
}

void Labyrinth::floorCell(Cell &cell) {
	cell.dungeonFloorA();
}

void Labyrinth::wallCell(Cell &cell) {
	cell.dungeonWallA();
}

void Labyrinth::wallItemCell(Cell &cell) {
	cell.dungeonWallA();
}

void Labyrinth::apply_backtrack(MapPrototype &map, int cX, int cY) {
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

void Labyrinth::remove_dead_end(MapPrototype &map) {
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

bool Labyrinth::is_dead_end(MapPrototype &map, int i, int j) {
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

Dungeon::Dungeon() {}

void Dungeon::apply(MapPrototype &map) {
	//We make sure the genrated map has enough floors
	//In the other case we generate another
	do {
		apply_loop(map);
	} while (flood(map) < (map.x*map.y/2));
	//Here remove dead end convcert to wall all useless corridors
	remove_dead_end(map);
}

std::string Dungeon::getRandomName() {
	return NameGenerator::dungeonName();
}

void Dungeon::floorCell(Cell &cell) {
	cell.dungeonFloorA();
}

void Dungeon::wallCell(Cell &cell) {
	cell.dungeonWallA();
}

void Dungeon::wallItemCell(Cell &cell) {
	//cell.dungeonWallItemA();
	cell.dungeonFloorA();
	Obstacle o;
	o.tableA();
	cell.obstacles.push_front(o);
}

void Dungeon::apply_loop(MapPrototype &map) {
	//First all the cells are wall
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
				map.cell[i][j] = WALL;
	//Then, for each odd cell (if it's a wall)
	//We can make a new room appear (with an odd size)
	for (int i=1;i<(map.x-1);i+=2)
		for (int j=1;j<(map.y-1);j+=2) {
			if (map.cell[i][j] == FLOOR)
				continue;
			if (rand()%2)
				continue;
			int maxI = (rand()%9)+3;
			int maxJ = (rand()%9)+3;
			//We draw an random number of entries
			if (draw_room(map, i, j, maxI, maxJ)) {
				draw_entries(map, i, j, maxI, maxJ);
			}
		}
	//Then for each odd cell where there's no room
	//We fill ot with random corridors
	for (int i=1;i<(map.x-1);i+=2)
		for (int j=1;j<(map.y-1);j+=2)
				if (map.cell[i][j] == WALL)
					draw_corridor(map, i, j);
	//Finally temp wall/floor are converted to real wall/floor
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++) {
			if (map.cell[i][j] == WALL<<4)
				map.cell[i][j] = WALL;
			if (map.cell[i][j] == FLOOR<<4)
				map.cell[i][j] = FLOOR;
		}
}

bool Dungeon::draw_room(MapPrototype &map, int i, int j, int &maxI, int &maxJ) {
	//We reduce the size of te room if there not enough space
	while ((maxI+i) >= (map.x))
		maxI--;
	while ((maxJ+j) >= (map.y))
		maxJ--;
	int turnI = 0;
	//We check if the space is a free space (all cells are walls)
	for (int ii=i;ii<(i+maxI);ii++) {
		turnI++;
		int turnJ = 0;
		for (int jj=j;jj<(j+maxJ);jj++) {
			turnJ++;
			if (map.cell[ii][jj] == WALL<<4) {
				ii = i+maxI;
				jj = j+maxJ;
				if (turnI > turnJ)
					maxI = turnI;
				else
					maxJ = turnJ;
			}
		}
	}
	//We reduce the size to an odd number
	if (!(maxI%2))
		maxI--;
	if (!(maxJ%2))
		maxJ--;
	if ((maxI < 3) || (maxJ < 3))
		return false;
	//Then we fill the room with floors
	for (int ii=i-1;ii<(i+1+maxI);ii++)
		for (int jj=j-1;jj<(j+1+maxJ);jj++)
			if ((ii==i-1)||(jj==j-1)||(ii==i+maxI)||(jj==j+maxJ))
				map.cell[ii][jj] = WALL<<4;
			else
				map.cell[ii][jj] = FLOOR;
	return true;
}

void Dungeon::draw_entries(MapPrototype &map, int i, int j, int maxI, int maxJ) {
	//The number of entires is computed with the size of the room
	int nEntries = 1+(rand()%(maxI+maxJ))/6;
	//We place the entries around the room
	for (int t=0;t<=nEntries;t++) {
		int dir1 = rand()%2;
		int dir2 = rand()%2;
		if ((i <= 1) && !dir1)
			dir2 = 1;
		else if ((j <= 1) && dir1)
			dir2 = 1;
		else if (i <= (map.x-2) && !dir1)
			dir2 = 0;
		else if (j <= (map.y-2) && dir1)
			dir2 = 0;
		if (dir1) {
			int dist = (rand()%maxI)+i;
			dist -= (dist%2 == 0);
			map.cell[dist][(j-1)+dir2*(maxJ+1)] = DOOR;
		}
		else {
			int dist = (rand()%maxJ)+j;
			dist -= (dist%2 == 0);
			map.cell[(i-1)+dir2*(maxI+1)][dist] = DOOR;
		}
	}	
}

void Dungeon::draw_corridor(MapPrototype &map, int i, int j) {
	//The algorithm is almost the same that maze generation
	map.cell[i][j] = FLOOR<<4;
	int dir = rand()%4;
	int sDir = 2*(rand()%2)+1;
	for (int t=0;t<4;t++) {
		if (((i+2*dirI(dir)) <= 0) || ((i+2*dirI(dir)) >= (map.x-1)))
			continue;
		if (((j+2*dirJ(dir)) <= 0) || ((j+2*dirJ(dir)) >= (map.y-1)))
			continue;
		if (map.cell[i+2*dirI(dir)][j+2*dirJ(dir)] == WALL) {
			map.cell[i+dirI(dir)][j+dirJ(dir)] = FLOOR<<4;
			draw_corridor(map, i+2*dirI(dir), j+2*dirJ(dir));
		}
		dir = (dir+sDir)%4;
	}
}

void Dungeon::remove_dead_end(MapPrototype &map) {
	for (int i=1;i<(map.x-1);i+=2)
		for (int j=1;j<(map.y-1);j+=2)
			if (map.cell[i][j] != WALL)
				remove_corridor(map, i, j);
}

void Dungeon::remove_corridor(MapPrototype &map, int i, int j) {
	//The algorithm is the same as flood algorithm
	int count = 0;
	if (map.cell[i-1][j] != WALL)
		count++;
	if (map.cell[i+1][j] != WALL)
		count++;
	if (map.cell[i][j-1] != WALL)
		count++;
	if (map.cell[i][j+1] != WALL)
		count++;
	if (count < 2) {
		map.cell[i][j] = WALL;
		if (map.cell[i-1][j] != WALL) {
			remove_corridor(map,i-1,j);
		}
		if (map.cell[i+1][j] != WALL) {
			remove_corridor(map,i+1,j);
		}
		if (map.cell[i][j-1] != WALL) {
			remove_corridor(map,i,j-1);
		}
		if (map.cell[i][j+1] != WALL) {
			remove_corridor(map,i,j+1);
		}
	}
}

int Dungeon::dirI(int dir) {
	switch (dir) {
		case 0 : return 1;
		case 2 : return -1;
	}
	return 0;
}

int Dungeon::dirJ(int dir) {
	switch (dir) {
		case 1 : return 1;
		case 3 : return -1;
	}
	return 0;
}