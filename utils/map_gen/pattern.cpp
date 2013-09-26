#include "pattern.h"

Pattern::Pattern() {}

int Pattern::flood(Map &map) {
	int fX,fY;
	int k = 0;
	do {
		fX = rand()%map.x;
		fY = rand()%map.y;
	} while (map.cell[fX][fY]);
	flood_rec(map, fX, fY);
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

void Pattern::flood_rec(Map &map, int fX, int fY) {
	if (map.cell[fX][fY] == 0)
		map.cell[fX][fY] = 2;
	if (map.cell[fX][fY] == 3)
		map.cell[fX][fY] = 4;
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

void Random::apply(Map &map) {
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++) {
			map.cell[i][j] = rand()%2;
		}
}

Cavern::Cavern() {}

void Cavern::apply(Map &map) {
	do
		apply_loop(map);
	while (flood(map) < (map.x*map.y)/3);
}

void Cavern::apply_loop(Map &map) {
	int toWall = 45;
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
			if ((i==0)||(i==(map.x-1))||(j==0)||(j==(map.y-1)))
				map.cell[i][j] = 1;
			else
				map.cell[i][j] = (rand()%100)<toWall;
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
		for (int i=1;i<map.x-1;i++)
			for (int j=1;j<map.y-1;j++)
				map.cell[i][j] = copy[i][j];
	}
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

void Labyrinth::apply(Map &map) {
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
	apply_backtrack(map, 1, 1);
	remove_dead_end(map);
}

void Labyrinth::apply_backtrack(Map &map, int cX, int cY) {
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

void Labyrinth::remove_dead_end(Map &map) {
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

bool Labyrinth::is_dead_end(Map &map, int i, int j) {
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

void Dungeon::apply(Map &map) {
	do {
		apply_loop(map);
	} while (flood(map) < (map.x*map.y/2));
	remove_dead_end(map);
}

void Dungeon::apply_loop(Map &map) {
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++)
				map.cell[i][j] = 1;
	for (int i=1;i<(map.x-1);i+=2)
		for (int j=1;j<(map.y-1);j+=2) {
			if (map.cell[i][j] == 0)
				continue;
			if (rand()%2)
				continue;
			int maxI = (rand()%9)+3;
			int maxJ = (rand()%9)+3;
			if (draw_room(map, i, j, maxI, maxJ)) {
				draw_entries(map, i, j, maxI, maxJ);
			}
		}
	for (int i=1;i<(map.x-1);i+=2)
		for (int j=1;j<(map.y-1);j+=2)
				if (map.cell[i][j] == 1)
					draw_corridor(map, i, j);
	for (int i=0;i<map.x;i++)
		for (int j=0;j<map.y;j++) {
			if (map.cell[i][j] == 2)
				map.cell[i][j] = 1;
			if (map.cell[i][j] == 5)
				map.cell[i][j] = 0;
		}
}

bool Dungeon::draw_room(Map &map, int i, int j, int &maxI, int &maxJ) {
	while ((maxI+i) >= (map.x))
		maxI--;
	while ((maxJ+j) >= (map.y))
		maxJ--;
	int turnI = 0;
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
	if (!(maxI%2))
		maxI--;
	if (!(maxJ%2))
		maxJ--;
	if ((maxI < 3) || (maxJ < 3))
		return false;
	for (int ii=i-1;ii<(i+1+maxI);ii++)
		for (int jj=j-1;jj<(j+1+maxJ);jj++)
			if ((ii==i-1)||(jj==j-1)||(ii==i+maxI)||(jj==j+maxJ))
				map.cell[ii][jj] = 2;
			else
				map.cell[ii][jj] = 0;
	return true;
}

void Dungeon::draw_entries(Map &map, int i, int j, int maxI, int maxJ) {
	int nEntries = 1+(rand()%(maxI+maxJ))/6;
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

void Dungeon::draw_corridor(Map &map, int i, int j) {
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

void Dungeon::remove_dead_end(Map &map) {
	for (int i=1;i<(map.x-1);i+=2)
		for (int j=1;j<(map.y-1);j+=2)
			if (map.cell[i][j] != 1)
				remove_corridor(map, i, j);
}

void Dungeon::remove_corridor(Map &map, int i, int j) {
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