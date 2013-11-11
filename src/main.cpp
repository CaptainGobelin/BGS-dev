#include "headers/gameController.h"

sf::RenderWindow GameWindow::window;
sf::View GameWindow::viewGame;
sf::View GameWindow::viewInt;

int OptionsFile::frameLimit = 50;
bool OptionsFile::vSync = true;
sf::Keyboard::Key OptionsFile::mapKey = sf::Keyboard::M;
sf::Keyboard::Key OptionsFile::upKey = sf::Keyboard::Up;
sf::Keyboard::Key OptionsFile::downKey = sf::Keyboard::Down;
sf::Keyboard::Key OptionsFile::rightKey = sf::Keyboard::Right;
sf::Keyboard::Key OptionsFile::leftKey = sf::Keyboard::Left;

sf::Texture Textures::texturesStart;
sf::Texture Textures::texturesCharacters;
sf::Texture Textures::texturesFloors;
sf::Texture Textures::texturesWalls;
sf::Texture Textures::texturesInterface;
sf::Texture Textures::texturesMap;
sf::Texture Textures::texturesMenu;
sf::Texture Textures::texturesArmorOn;
sf::Texture Textures::texturesArmorOff;
sf::Texture Textures::texturesWeaponOn;
sf::Texture Textures::texturesWeaponOff;

int main(int argc, char *argv[]) {
	//Initialize game
	GameController game;
	//Launch the game
	game.launch();
	return 0;
}
