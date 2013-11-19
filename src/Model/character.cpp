#include "../headers/Model/character.h"

Character::Character() {}

Character::Character(std::string name, int raceChoice, std::string map) {
	this->name = name;
	this->map = map;
	this->x = 2;
	this->y = 2;
	this->race = Race(raceChoice);
	this->attributes[ATTR_VIEW] = 9;
}

void Character::draw() {
	GameWindow::window.setView(GameWindow::viewGame);
	race.setPosition((H_WINDOW-T_TILES)/2,(H_WINDOW-T_TILES)/2);
	GameWindow::window.draw(race.getBody());
}

bool Character::move(int dX, int dY, const Map& map) {
	int newX = std::max(0,std::min(map.getLength(), x+dX));
	int newY = std::max(0,std::min(map.getWidth(), y+dY));
	if (!map.cell[newX][newY].isSolid()) {
		setPosition(newX, newY);
		return true;
	}
	if (!map.cell[newX][newY].obstacles.empty())
		map.cell[newX][newY].obstacles.begin()->broke();
	return false;
}

void Character::checkView(Map& map) {
	for (int j=std::max(0,y-attributes[ATTR_VIEW]);j<std::min(map.getWidth(),y+attributes[ATTR_VIEW]+1);j++)
		for (int i=std::max(0,x-attributes[ATTR_VIEW]);i<std::min(map.getLength(),x+attributes[ATTR_VIEW]+1);i++)
			if (std::abs(x-i)+std::abs(y-j) <= attributes[ATTR_VIEW])
				checkLine(map,i,j);
	for (int j=std::max(0,y-attributes[ATTR_VIEW]);j<std::min(map.getWidth(),y+attributes[ATTR_VIEW]+1);j++)
		for (int i=std::max(0,x-attributes[ATTR_VIEW]);i<std::min(map.getLength(),x+attributes[ATTR_VIEW]+1);i++)
			if (map.cell[i][j].isViewed())
				map.cell[i][j].setVisited(true);
}

void Character::checkLine(Map &map, int i, int j) {
	//A standard Bresenham algorithm
	bool see = true;
	int dx = abs(i - x);
	int dy = abs(j - y);
	float e = dx-dy;
	int sx = (x < i) ? 1 : -1;
	int sy = (y < j) ? 1 : -1;
	int xx = x;
	int yy = y;
	bool stop = false;
	while (!stop) {
		if (see)
			map.cell[xx][yy].setViewed(true);
		if (!map.cell[xx][yy].isTransparent())
			break;
		if ((xx == i) && (yy == j))
			break;
		float e2 = 2*e;
		if (e2 > -dx) {
			e -= dy;
			xx += sx;
		}
		if (e2 < dx) {
			e += dx;
			yy += sy;
		}
	}
}

void Character::loadSprite() {
	race.loadSprite();
}

void Character::goToStart(Map &map, std::string mapName) {
	//Check if the entrance already exists
	for (int i=0;i<map.getLength();i++)
		for (int j=0;j<map.getWidth();j++)
			if (!map.cell[i][j].exits.empty())
				if (map.cell[i][j].exits.begin()->getDestCode().compare(this->map) == 0) {
					map.cell[i][j].exits.begin()->setDestName(mapName);
					this->x = i;
					this->y = j;
					return;
				}
	//If not, generate one
	int rX, rY;
	do {
		rX = rand()%map.getLength();
		rY = rand()%map.getWidth();
	} while (map.cell[rX][rY].isSolid() || !map.cell[rX][rY].exits.empty());
	map.cell[rX][rY].dungeonExit();
	map.cell[rX][rY].exits.push_front(MapExit(this->map));
	map.cell[rX][rY].exits.begin()->setDestName(mapName);
	this->x = rX;
	this->y = rY;
}