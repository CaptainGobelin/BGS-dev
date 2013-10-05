#include "../headers/utils/mapPrototype.h"

MapPrototype::MapPrototype() {
	this->x = 0;
	this->y = 0;
}

MapPrototype::MapPrototype(int newX, int newY) {
	this->x = newX;
	this->y = newY;
	cell = new int* [x];
	for (int i=0;i<x;i++)
            cell[i] = new int [y];
    for (int j=0;j<y;j++)
        for (int i=0;i<x;i++) {
        	cell[i][j] = 0;
        }
}

MapPrototype::~MapPrototype() {
	for (int i=0;i<x;i++)
		delete [] this->cell[i];
	delete [] this->cell;
}