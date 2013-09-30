#include "../headers/Model/race.h"

Race::Race() {
	this->raceCode = UNDEFINED_CODE;
}

Race::Race(int code) {
	raceCode = code;
	switch (raceCode) {
		case HUMAN_CODE:
			humanRace();
			break;
		default:
			humanRace();
	}
}

void Race::setPosition(float x, float y) {
	this->body.setPosition(x,y);
}

void Race::loadSprite() {
	switch (raceCode) {
		case HUMAN_CODE:
			humanRace();
			break;
		default:
			humanRace();
	}
}

void Race::humanRace() {
	this->raceCode = HUMAN_CODE;
	this->attributes = 0;
	this->body.setTexture(Textures::texturesCharacters);
}