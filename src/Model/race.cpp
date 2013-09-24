#include "../headers/Model/race.h"

Race::Race() {
	this->raceCode = UNDEFINED_CODE;
}

void Race::setPosition(float x, float y) {
	this->body.setPosition(x,y);
}

HumanRace::HumanRace() {
	this->raceCode = HUMAN_CODE;
	this->attributes = 0;
	this->body.setTexture(Textures::texturesCharacters);
}