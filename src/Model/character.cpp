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