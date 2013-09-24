#ifndef RACE_H
#define RACE_H

#include "../utils/const.h"
#include "../utils/lib.h"

#include "textures.h"
#include "../GUI/gameWindow.h"

class Race {
	public :
		Race();
		/*const sf::Sprite &getFaceTop() const {return faceTop;}
		void setFaceTop(const sf::Sprite &newFaceTop) {faceTop=newFaceTop;}
		const sf::Sprite &getFaceBottom() const {return faceBottom;}
		void setFaceBottom(const sf::Sprite &newFaceBottom) {faceBottom=newFaceBottom;}*/
		const sf::Sprite &getBody() const {return body;}
		void setBody(const sf::Sprite &newBody) {body=newBody;}
		const int &getAttributes() const {return attributes;}
		const int &getRaceCode() const {return raceCode;}

		void setPosition(float x, float y);

	protected :
		/*sf::Sprite faceTop;
		sf::Sprite faceBottom;*/
		sf::Sprite body;
		int attributes;
		int raceCode;
};

class HumanRace : public Race {
	public :
		HumanRace();
};

#endif