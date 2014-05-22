#include "headers/gameController.h"

sf::RenderWindow GameWindow::window;
sf::View GameWindow::viewGame;
sf::View GameWindow::viewInt;

//Default options
int OptionsFile::frameLimit = 50;
bool OptionsFile::vSync = true;
sf::Keyboard::Key OptionsFile::mapGameKey = sf::Keyboard::M;
sf::Keyboard::Key OptionsFile::inventoryGameKey = sf::Keyboard::I;
sf::Keyboard::Key OptionsFile::upGameKey = sf::Keyboard::Up;
sf::Keyboard::Key OptionsFile::downGameKey = sf::Keyboard::Down;
sf::Keyboard::Key OptionsFile::rightGameKey = sf::Keyboard::Right;
sf::Keyboard::Key OptionsFile::leftGameKey = sf::Keyboard::Left;
sf::Keyboard::Key OptionsFile::menuGameKey = sf::Keyboard::Escape;
sf::Keyboard::Key OptionsFile::validGameKey = sf::Keyboard::Return;
sf::Keyboard::Key OptionsFile::exitGameKey = sf::Keyboard::Q;
sf::Keyboard::Key OptionsFile::confirmGameKey = sf::Keyboard::Y;
sf::Keyboard::Key OptionsFile::cancelGameKey = sf::Keyboard::N;

sf::Texture Textures::texturesStart;
sf::Texture Textures::texturesCharacters;
sf::Texture Textures::texturesFloors;
sf::Texture Textures::texturesWalls;
sf::Texture Textures::texturesInterface;
sf::Texture Textures::texturesMap;
sf::Texture Textures::texturesInventory;
sf::Texture Textures::texturesMenu;
sf::Texture Textures::texturesArmorOn;
sf::Texture Textures::texturesArmorOff;
sf::Texture Textures::texturesWeaponOn;
sf::Texture Textures::texturesWeaponOff;
sf::Texture Textures::texturesObstacles;
sf::Texture Textures::texturesDoors;

int main(int argc, char *argv[]) {
	//Initialize game
	GameController game;
	//Launch the game
	game.launch();
	return 0;
}
