#include "mapGenerator.h"
#include "mapGenUtils.h"
#include "pattern.h"

#define CLICK_BUTTON (CLICK_GENERATE || CLICK_CAVERN || CLICK_RANDOM || CLICK_LABYRINTH || CLICK_DUNGEON \
|| CLICK_M || CLICK_L)
#define CLICK_GENERATE ((event.type == sf::Event::MouseButtonPressed)&&\
(sf::Mouse::getPosition(window).x>640)&&(sf::Mouse::getPosition(window).y>520)\
&&(sf::Mouse::getPosition(window).x<815)&&(sf::Mouse::getPosition(window).y<570))
#define CLICK_CAVERN ((event.type == sf::Event::MouseButtonPressed)&&\
(sf::Mouse::getPosition(window).x>10)&&(sf::Mouse::getPosition(window).y>570)\
&&(sf::Mouse::getPosition(window).x<130)&&(sf::Mouse::getPosition(window).y<610))
#define CLICK_RANDOM ((event.type == sf::Event::MouseButtonPressed)&&\
(sf::Mouse::getPosition(window).x>10)&&(sf::Mouse::getPosition(window).y>620)\
&&(sf::Mouse::getPosition(window).x<130)&&(sf::Mouse::getPosition(window).y<660))
#define CLICK_LABYRINTH ((event.type == sf::Event::MouseButtonPressed)&&\
(sf::Mouse::getPosition(window).x>140)&&(sf::Mouse::getPosition(window).y>570)\
&&(sf::Mouse::getPosition(window).x<260)&&(sf::Mouse::getPosition(window).y<610))
#define CLICK_DUNGEON ((event.type == sf::Event::MouseButtonPressed)&&\
(sf::Mouse::getPosition(window).x>140)&&(sf::Mouse::getPosition(window).y>620)\
&&(sf::Mouse::getPosition(window).x<260)&&(sf::Mouse::getPosition(window).y<660))
#define CLICK_M ((event.type == sf::Event::MouseButtonPressed)&&\
(sf::Mouse::getPosition(window).x>902)&&(sf::Mouse::getPosition(window).y>4)\
&&(sf::Mouse::getPosition(window).x<985)&&(sf::Mouse::getPosition(window).y<42))
#define CLICK_L ((event.type == sf::Event::MouseButtonPressed)&&\
(sf::Mouse::getPosition(window).x>902)&&(sf::Mouse::getPosition(window).y>44)\
&&(sf::Mouse::getPosition(window).x<985)&&(sf::Mouse::getPosition(window).y<82))


sf::RenderWindow window;
sf::View view;

int main(int argc, char *argv[]) {
	sf::Texture textureMap;
	textureMap.loadFromFile("data/fond.png");
	sf::Sprite spriteMap;
	spriteMap.setTexture(textureMap);
	window.create(sf::VideoMode(L_WINDOW, H_WINDOW, 32), "Map Generator");
	view.reset(sf::FloatRect(0, 0, L_WINDOW, H_WINDOW));
	window.setView(view);
	window.draw(spriteMap);
	window.display();
	srand (time(NULL));
	MapGenerator *mapGenerator;
	MapGenerator_L lGenerator;
	MapGenerator_M mGenerator;
	mapGenerator = &mGenerator;
	sf::Event event;
	Pattern *pattern;
	Random randomPattern;
	Cavern cavernPattern;
	Labyrinth labyrinthPattern;
	Dungeon dungeonPattern;
	pattern = &dungeonPattern;
	do {
		window.draw(spriteMap);
		Map map = mapGenerator->generate();
		pattern->apply(map);
		/*for (int i=0;i<30;i++) {
			int rX = rand()%map.x;
			int rY = rand()%map.y;
			if (MapGenUtils::canAddWall(map, rX, rY))
				map.cell[rX][rY] = 2;
		}*/
		mapGenerator->draw(map);
		window.display();
		do
			window.waitEvent(event);
		while ((event.type != sf::Event::Closed) && (!CLICK_BUTTON));
		if (CLICK_CAVERN)
			pattern = &cavernPattern;
		else if (CLICK_RANDOM)
			pattern = &randomPattern;
		else if (CLICK_LABYRINTH)
			pattern = &labyrinthPattern;
		else if (CLICK_DUNGEON)
			pattern = &dungeonPattern;
		else if (CLICK_M)
			mapGenerator = &mGenerator;
		else if (CLICK_L)
			mapGenerator = &lGenerator;

	} while (event.type != sf::Event::Closed);
	return 0;
}
