#ifndef MAPGEN_H
#define MAPGEN_H

#define OR_X 35
#define OR_Y 35

#include "map.h"

class MapGenerator {
	public :
		MapGenerator();
		virtual Map generate() = 0;
		virtual void draw(Map &map) = 0;
	private :
		sf::Texture textureSol;
		sf::Texture textureBloc;
		sf::Texture textureDoor;
		sf::Sprite spriteSol;
		sf::Sprite spriteBloc;
		sf::Sprite spriteDoor;
};

class MapGenerator_L : public MapGenerator {
	public :
		MapGenerator_L();
		virtual Map generate();
		virtual void draw(Map &map);
	private :
		sf::Texture textureSol;
		sf::Texture textureBloc;
		sf::Texture textureDoor;
		sf::Sprite spriteSol;
		sf::Sprite spriteBloc;
		sf::Sprite spriteDoor;
};

class MapGenerator_M : public MapGenerator {
	public :
		MapGenerator_M();
		virtual Map generate();
		virtual void draw(Map &map);
	private :
		sf::Texture textureSol;
		sf::Texture textureBloc;
		sf::Texture textureDoor;
		sf::Sprite spriteSol;
		sf::Sprite spriteBloc;
		sf::Sprite spriteDoor;
};

#endif