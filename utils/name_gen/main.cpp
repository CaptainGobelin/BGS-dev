#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>

#include "nameGenerator.h"

sf::RenderWindow window;
sf::View view;

int main(int argc, char *argv[]) {
	NameGenerator nameGen;
	sf::Font font;
	font.loadFromFile("pcsenior.ttf");
	sf::Text text("Press Enter to generate",font,20);
	text.setPosition(10,13);
	text.setColor(sf::Color(sf::Color::White));
	window.create(sf::VideoMode(470, 50, 32), "Name Generator");
	view.reset(sf::FloatRect(0, 0, 470, 50));
	window.setView(view);
	srand (time(NULL));
	sf::Event event;
	do {
		window.clear();
		window.draw(text);
		window.display();
		bool reDo = true;
		do {
			window.waitEvent(event);
			if (event.type == sf::Event::Closed)
				return 0;
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Return)
					reDo = false;
		} while (reDo);
		text.setString(nameGen.generate());
	} while (event.type != sf::Event::Closed);
	return 0;
}
