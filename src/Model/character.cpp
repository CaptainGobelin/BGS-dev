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
				map.cell[i][j].setViewed(true);
	checkVer(map, 1);
	checkVer(map, -1);
	checkHor(map, 1);
	checkHor(map, -1);
	for (int j=std::max(0,y-attributes[ATTR_VIEW]);j<std::min(map.getWidth(),y+attributes[ATTR_VIEW]+1);j++)
		for (int i=std::max(0,x-attributes[ATTR_VIEW]);i<std::min(map.getLength(),x+attributes[ATTR_VIEW]+1);i++)
			if (map.cell[i][j].isViewed())
				map.cell[i][j].setVisited(true);
}

void Character::checkVer(Map& map, int dir) {
	int maxJ = std::max(-1,y-dir*(attributes[ATTR_VIEW]+1));
	if (dir == -1)
		maxJ = std::min(map.getWidth(), y-dir*(attributes[ATTR_VIEW]+1));
	for (int j=y-dir;dir*j>dir*maxJ;j-=dir) {
		for (int i=std::max(0,x-std::abs(y-j));i<std::min(map.getLength(),x+std::abs(y-j)+1);i++)
			if (!map.cell[i][j].isTransparent()) {
				int i2=i+1;
				bool stop = false;
				while (!stop) {
					if (i2 >= std::min(map.getLength(),x+std::abs(y-j)+1)) {
						stop = true;
						i2--;
					}
					else if (map.cell[i2][j].isTransparent()) {
						stop = true;
						i2--;
					}
					else {
						i2++;
					}
				}
				for (int j2=j-dir;dir*j2>dir*maxJ;j2-=dir) {
					int start = i+(float(dir*std::abs(j2-j))*float(-(i-x-0.5)/(j-y+dir*0.5)));
					int end = i2+ceil(float(dir*std::abs(j2-j))*float(-(i2-x+0.5)/(j-y+dir*0.5)));
					for (int iAct=std::max(0,start);iAct<std::min(map.getLength(),end+1);iAct++)
						map.cell[iAct][j2].setViewed(false);
				}
				i = i2;
			}
	}
}

void Character::checkHor(Map& map, int dir) {
	int maxI = std::max(-1,x-dir*(attributes[ATTR_VIEW]+1));
	if (dir == -1)
		maxI = std::min(map.getLength(), x-dir*(attributes[ATTR_VIEW]+1));
	for (int i=x-dir;dir*i>dir*maxI;i-=dir) {
		for (int j=std::max(0,y-std::abs(x-i));j<std::min(map.getWidth(),y+std::abs(x-i)+1);j++)
			if (!map.cell[i][j].isTransparent()) {
				int j2=j+1;
				bool stop = false;
				while (!stop) {
					if (j2 >= std::min(map.getWidth(),y+std::abs(x-i)+1)) {
						stop = true;
						j2--;
					}
					else if (map.cell[i][j2].isTransparent()) {
						stop = true;
						j2--;
					}
					else {
						j2++;
					}
				}
				for (int i2=std::max(0,i-dir);dir*i2>dir*maxI;i2-=dir) {
					int start = j+(float(dir*std::abs(i2-i))*float(-(j-y-0.5)/(i-x+dir*0.5)));
					int end = j2+ceil(float(dir*std::abs(i2-i))*float(-(j2-y+0.5)/(i-x+dir*0.5)));
					for (int jAct=std::max(0,start);jAct<std::min(map.getWidth(),end+1);jAct++)
						map.cell[i2][jAct].setViewed(false);
				}
				j = j2;
			}
	}
}

void Character::loadSprite() {
	race.loadSprite();
}