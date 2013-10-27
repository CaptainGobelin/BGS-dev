#include "../headers/Model/mapExit.h"

MapExit::MapExit(std::string code/*=""*/, int dep/*=0*/) {
	this->destCode = code;
	this->destName = "???";
	this->dependencies = dep;
}