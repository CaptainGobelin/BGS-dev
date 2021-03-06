#include "mapGenerator.h"

extern sf::RenderWindow window;
extern sf::View view;

MapGenerator::MapGenerator() {
}

MapGenerator_L::MapGenerator_L() {
	textureSol.loadFromFile("data/mSol_L.png");
	textureBloc.loadFromFile("data/mBloc_L.png");
	textureDoor.loadFromFile("data/mDoor_L.png");
	textureObj.loadFromFile("data/mObj_L.png");
	spriteSol.setTexture(textureSol);
	spriteBloc.setTexture(textureBloc);
	spriteDoor.setTexture(textureDoor);
	spriteObj.setTexture(textureObj);
}

Map MapGenerator_L::generate() {
	Map map(rand() % 50 + 50,rand() % 50 + 50);
	return map;
}

void MapGenerator_L::draw(Map &map) {
	int curX = OR_X;
	int curY = OR_Y;
	for (int i=0;i<map.x;i++) {
		curY = OR_Y;
		for (int j=0;j<map.y;j++) {
			if (map.cell[i][j] == 1) {
				spriteBloc.setPosition(curX,curY);
				window.draw(spriteBloc);
			}
			else if (map.cell[i][j] == 3)  {
				spriteDoor.setPosition(curX,curY);
				window.draw(spriteDoor);
			}
			else if (map.cell[i][j] == 0) {
				spriteSol.setPosition(curX,curY);
				window.draw(spriteSol);
			}
			else if (map.cell[i][j] == 2) {
				spriteObj.setPosition(curX,curY);
				window.draw(spriteObj);
			}
			curY += 5;
		}
		curX +=5;
	}
}

MapGenerator_M::MapGenerator_M() {
	textureSol.loadFromFile("data/mSol_M.png");
	textureBloc.loadFromFile("data/mBloc_M.png");
	textureDoor.loadFromFile("data/mDoor_M.png");
	textureObj.loadFromFile("data/mObj_M.png");
	spriteSol.setTexture(textureSol);
	spriteBloc.setTexture(textureBloc);
	spriteDoor.setTexture(textureDoor);
	spriteObj.setTexture(textureObj);
}

Map MapGenerator_M::generate() {
	Map map(rand() % 25 + 25,rand() % 25 + 25);
	return map;
}

void MapGenerator_M::draw(Map &map) {
	int curX = OR_X;
	int curY = OR_Y;
	for (int i=0;i<map.x;i++) {
		curY = OR_Y;
		for (int j=0;j<map.y;j++) {
			if (map.cell[i][j] == 1) {
				spriteBloc.setPosition(curX,curY);
				window.draw(spriteBloc);
			}
			else if (map.cell[i][j] == 3)  {
				spriteDoor.setPosition(curX,curY);
				window.draw(spriteDoor);
			}
			else if (map.cell[i][j] == 0) {
				spriteSol.setPosition(curX,curY);
				window.draw(spriteSol);
			}
			else if (map.cell[i][j] == 2) {
				spriteObj.setPosition(curX,curY);
				window.draw(spriteObj);
			}
			curY += 10;
		}
		curX +=10;
	}
}