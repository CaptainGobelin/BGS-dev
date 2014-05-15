#include "../headers/utils/dungeon.h"

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
			draw_room(map, i, j, maxI, maxJ);
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

	bool toDraw = rand()%4;
	//Then we fill the room with floors
	if (toDraw) {
		toDraw = false;
		int chRoom = -1;
		for (int k=0;k<NB_ROOMS;k++)
			if ((roomsSizes[k][0] == (maxI+2)) && roomsSizes[k][1] == (maxJ+2)) {
				toDraw = true;
				chRoom = k;
			}
		if (toDraw) {
			for (int ii=0;ii<(maxI+2);ii++) {
				for (int jj=0;jj<(maxJ+2);jj++) {
					if ((i <= 1) || (j <= 1) || (i >= map.x-2) || (j >= map.y+2))
						map.cell[ii+i-1][jj+j-1] = WALL<<4;
					else if ((rooms[chRoom][ii][jj] == WALL) &&
						((ii == 0) || (jj == 0)) || (ii == maxI+1) || (jj == maxJ+1))
						map.cell[ii+i-1][jj+j-1] = WALL<<4;
					else
						map.cell[ii+i-1][jj+j-1] = rooms[chRoom][ii][jj];
				}
			}
		}
	}
	if (!toDraw) {
		for (int ii=i-1;ii<(i+1+maxI);ii++)
			for (int jj=j-1;jj<(j+1+maxJ);jj++)
				if ((ii==i-1)||(jj==j-1)||(ii==i+maxI)||(jj==j+maxJ))
					map.cell[ii][jj] = WALL<<4;
				else
					map.cell[ii][jj] = FLOOR;
		draw_entries(map, i, j, maxI, maxJ);
	}
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
	for (int i=1;i<(map.x-1);i++)
		for (int j=1;j<(map.y-1);j++)
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