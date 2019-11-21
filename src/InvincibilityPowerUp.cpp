#include "InvincibilityPowerUp.h"
#include "Obstacle.h"
#include "GameWindow.h"
#include "time.h"
#include "Entity.h"
#include <iostream>

#include <cmath>


InvincibilityPowerUp::InvincibilityPowerUp(GameWindow* window) : Obstacle(window, 0, 0, NULL, true, 10) {
	this->stage = 0;
	this->launching = false;
	this->ticks = 0;
	this->totalStages = 0;
};

InvincibilityPowerUp::~InvincibilityPowerUp() {

}

void InvincibilityPowerUp::generateObstacle() {
	int x = (GameWindow::GAME_WIDTH);

	int y = 380 - (rand() % (GameWindow::GAME_HEIGHT / 2));

	this->launching = true;

	Entity::setX(x);
	Entity::setY(y);

}

void InvincibilityPowerUp::handleCollision(Player* player) {
	//increment player's score
	window->setScore(window->getScore() + 10000);
	player->setMortality(false);
	window->getSoundMixer().playSound("coin");
	destroy();
}


void InvincibilityPowerUp::draw(Graphics& graphics) {

	if(!launching) {
		return;
	}


	setSprite(graphics.loadImage("star"));


	Entity::gameDraw(graphics);
}





