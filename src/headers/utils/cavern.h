#ifndef CAVERN_PAT_H
#define CAVERN_PAT_H

#include "lib.h"
#include "const.h"

#include "mapPrototype.h"
#include "nameGenerator.h"
#include "../Model/cell.h"

#include "mapPattern.h"

class Cavern : public MapPattern {
	public: 
		Cavern();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
		virtual void floorCell(Cell &cell);
		virtual void doorCell(Cell &cell);
		virtual void wallCell(Cell &cell);
		virtual void wallItemCell(Cell &cell);
};

#endif