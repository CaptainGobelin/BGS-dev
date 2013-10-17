#include "../headers/utils/mapPattern.h"

MapPattern::MapPattern() {}

int MapPattern::flood(MapPrototype &map) {
	int fX,fY;
	int k = 0;
	//We take a random floor
	do {
		fX = rand()%map.x;
		fY = rand()%map.y;
	} while (map.cell[fX][fY]);
	//And we start flooding from this cell
	flood_rec(map, fX, fY);
	//Then we replace flooded cells by normal cells
	//And non flooded cells by walls
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
			if (map.cell[i][j] == 0)
				map.cell[i][j] = 1;
			else if (map.cell[i][j] == 3)
				map.cell[i][j] = 1;
			else if (map.cell[i][j] == 2) {
				map.cell[i][j] = 0;
				k++;
			}
			else if (map.cell[i][j] == 4) {
				map.cell[i][j] = 3;
				k++;
			}
	return k;
}

void MapPattern::flood_rec(MapPrototype &map, int fX, int fY) {
	//We mark the cell flooded
	if (map.cell[fX][fY] == 0)
		map.cell[fX][fY] = 2;
	if (map.cell[fX][fY] == 3)
		map.cell[fX][fY] = 4;
	//We call the flood method on the adjacent cells
	if ((map.cell[fX-1][fY] == 3) || (map.cell[fX-1][fY] == 0))
		flood_rec(map,fX-1,fY);
	if ((map.cell[fX+1][fY] == 3) || (map.cell[fX+1][fY] == 0))
		flood_rec(map,fX+1,fY);
	if ((map.cell[fX][fY-1] == 3) || (map.cell[fX][fY-1] == 0))
		flood_rec(map,fX,fY-1);
	if ((map.cell[fX][fY+1] == 3) || (map.cell[fX][fY+1] == 0))
		flood_rec(map,fX,fY+1);
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

void Random::apply(MapPrototype &map) {
	//Cells are randomly floor of wall
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++) {
			map.cell[i][j] = rand()%2;
		}
}

Cavern::Cavern() {}

void Cavern::apply(MapPrototype &map) {
	//We make sure that the cavern has enough floors
	//In the other case we drop off the present one
	//And we generate an another cavern
	do
		apply_loop(map);
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

void Cavern::apply_loop(MapPrototype &map) {
	//It's a cellula automata algorithm
	//At te begining each cell is randomly convert
	//To a wall or a floor with toWall% chances to be a wall
	int toWall = 45;
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
			if ((i==0)||(i==(map.x-1))||(j==0)||(j==(map.y-1)))
				map.cell[i][j] = 1;
			else
				map.cell[i][j] = (rand()%100)<toWall;
	//Then we apply four times a simple algorithm
	//For each cell, if the number of neighboors (include the cell itself)
	//Is in [1..4] we convert it to a wall
	int copy[map.x][map.y];
	for (int turn=0;turn<4;turn++) {
		for (int i=1;i<map.x-1;i++)
			for (int j=1;j<map.y-1;j++) {
				int count1=0;
				for (int ii=i-1;ii<i+2;ii++)
					for (int jj=j-1;jj<j+2;jj++)
						count1 += map.cell[ii][jj];
				copy[i][j] = (count1 > 4) || (count1 < 1);
			}
		//Here we copy the map, to prepare the new step of the loop
		for (int i=1;i<map.x-1;i++)
			for (int j=1;j<map.y-1;j++)
				map.cell[i][j] = copy[i][j];
	}
	//Finally we convert isolated walls to floor (3 times to make it clean)
	for (int turn=0;turn<3;turn++) {
		for (int i=1;i<map.x-1;i++)
			for (int j=1;j<map.y-1;j++) {
				int count1=0;
				for (int ii=i-1;ii<i+2;ii++)
					for (int jj=j-1;jj<j+2;jj++)
						count1 += map.cell[ii][jj];
				copy[i][j] = (count1 > 4);
			}
		for (int i=1;i<map.x-1;i++)
			for (int j=1;j<map.y-1;j++)
				map.cell[i][j] = copy[i][j];
	}
}

Labyrinth::Labyrinth() {}

void Labyrinth::apply(MapPrototype &map) {
	//Maze generation is simple, it's a backtracking algorithm
	//Which generate perfect maze
	//First, all odd cells are floors
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
			if ((i==0)||(j==0)||(i==(map.x-1))||(j==(map.y-1)))
				map.cell[i][j] = 1;
			else {
				if ((i%2) && (j%2))
					map.cell[i][j] = 2;
				else
					map.cell[i][j] = 1;
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

void Labyrinth::apply_backtrack(MapPrototype &map, int cX, int cY) {
	//Backtrack method is a bit long but simple
	//We try to construct a way with random directions
	//When we are blocked, we try another direction
	map.cell[cX][cY] = 0;
	int turn = rand()%4;
	for (int k=0;k<4;k++) {
		switch (turn) {
			case 0: {
				if (cX != 1)
					if (map.cell[cX-2][cY] == 2) {
						map.cell[cX-1][cY] = 0;
						apply_backtrack(map, cX-2, cY);
					}
				break;
			}
			case 1: {
				if (cY < (map.y-2))
					if (map.cell[cX][cY+2] == 2) {
						map.cell[cX][cY+1] = 0;
						apply_backtrack(map, cX, cY+2);
					}
				break;
			}
			case 2: {
				if (cX < (map.x-2))
					if (map.cell[cX+2][cY] == 2) {
						map.cell[cX+1][cY] = 0;
						apply_backtrack(map, cX+2, cY);
					}
				break;
			}
			case 3: {
				if (cY != 1)
					if (map.cell[cX][cY-2] == 2) {
						map.cell[cX][cY-1] = 0;
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
							if ((i != 1) && (map.cell[i-1][j])) {
								map.cell[i-1][j] = 0;
								k = 4;
							}
							break;
						case 1:
							if ((i < (map.x-2-!(map.x%2))) && (map.cell[i+1][j])) {
								map.cell[i+1][j] = 0;
								k = 4;
							}
							break;
						case 2:
							if ((j != 1) && (map.cell[i][j-1])) {
								map.cell[i][j-1] = 0;
								k = 4;
							}
							break;
						case 3:
							if ((j < (map.y-2-!(map.y%2))) && (map.cell[i][j+1])) {
								map.cell[i][j+1] = 0;
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
	if (map.cell[i-1][j])
		count++;
	if (map.cell[i+1][j])
		count++;
	if (map.cell[i][j-1])
		count++;
	if (map.cell[i][j+1])
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

void Dungeon::apply_loop(MapPrototype &map) {
	//First all the cells are wall
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
				map.cell[i][j] = 1;
	//Then, for each odd cell (if it's a wall)
	//We can make a new room appear (with an odd size)
	for (int i=1;i<(map.x-1);i+=2)
		for (int j=1;j<(map.y-1);j+=2) {
			if (map.cell[i][j] == 0)
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
				if (map.cell[i][j] == 1)
					draw_corridor(map, i, j);
	//Finally temp wall/floor are converted to real wall/floor
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++) {
			if (map.cell[i][j] == 2)
				map.cell[i][j] = 1;
			if (map.cell[i][j] == 5)
				map.cell[i][j] = 0;
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
			if (map.cell[ii][jj] == 2) {
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
				map.cell[ii][jj] = 2;
			else
				map.cell[ii][jj] = 0;
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
			map.cell[dist][(j-1)+dir2*(maxJ+1)] = 3;
		}
		else {
			int dist = (rand()%maxJ)+j;
			dist -= (dist%2 == 0);
			map.cell[(i-1)+dir2*(maxI+1)][dist] = 3;
		}
	}	
}

void Dungeon::draw_corridor(MapPrototype &map, int i, int j) {
	//The algorithm is almost the same that maze generation
	map.cell[i][j] = 5;
	int dir = rand()%4;
	int sDir = 2*(rand()%2)+1;
	for (int t=0;t<4;t++) {
		if (((i+2*dirI(dir)) <= 0) || ((i+2*dirI(dir)) >= (map.x-1)))
			continue;
		if (((j+2*dirJ(dir)) <= 0) || ((j+2*dirJ(dir)) >= (map.y-1)))
			continue;
		if (map.cell[i+2*dirI(dir)][j+2*dirJ(dir)] == 1) {
			map.cell[i+dirI(dir)][j+dirJ(dir)] = 5;
			draw_corridor(map, i+2*dirI(dir), j+2*dirJ(dir));
		}
		dir = (dir+sDir)%4;
	}
}

void Dungeon::remove_dead_end(MapPrototype &map) {
	for (int i=1;i<(map.x-1);i+=2)
		for (int j=1;j<(map.y-1);j+=2)
			if (map.cell[i][j] != 1)
				remove_corridor(map, i, j);
}

void Dungeon::remove_corridor(MapPrototype &map, int i, int j) {
	//The algorithm is the same as flood algorithm
	int count = 0;
	if (map.cell[i-1][j] != 1)
		count++;
	if (map.cell[i+1][j] != 1)
		count++;
	if (map.cell[i][j-1] != 1)
		count++;
	if (map.cell[i][j+1] != 1)
		count++;
	if (count < 2) {
		map.cell[i][j] = 1;
		if (map.cell[i-1][j] != 1) {
			remove_corridor(map,i-1,j);
		}
		if (map.cell[i+1][j] != 1) {
			remove_corridor(map,i+1,j);
		}
		if (map.cell[i][j-1] != 1) {
			remove_corridor(map,i,j-1);
		}
		if (map.cell[i][j+1] != 1) {
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