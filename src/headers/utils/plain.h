#ifndef PLAIN_PAT_H
#define PLAIN_PAT_H

#include "lib.h"
#include "const.h"

#include "mapPrototype.h"
#include "nameGenerator.h"
#include "../Model/cell.h"

#include "mapPattern.h"

class Plain : public MapPattern {
	public: 
		Plain();
		virtual void apply(MapPrototype &map);
		virtual std::string getRandomName();
		virtual void floorCell(Cell &cell);
		virtual void doorCell(Cell &cell);
		virtual void wallCell(Cell &cell);
		virtual void wallItemCell(Cell &cell);
};

#endif