#include "../headers/utils/plain.h"

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