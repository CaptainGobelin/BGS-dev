#include "../headers/Model/equipement.h"

Equipement::Equipement() {}

void Equipement::draw() {
	this->legs->setPosition((H_WINDOW-T_TILES)/2,(H_WINDOW-T_TILES)/2);
	GameWindow::window.draw(this->legs->getSpriteOn());
}