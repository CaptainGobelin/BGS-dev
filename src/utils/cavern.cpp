#include "../headers/utils/cavern.h"

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