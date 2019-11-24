#include "ZoomPowerUp.h"
#include "Obstacle.h"
#include "GameWindow.h"
#include "time.h"
#include "Entity.h"
#include <iostream>

#include <cmath>


ZoomPowerUp::ZoomPowerUp(GameWindow* window) : Obstacle(window, 0, 0, NULL, true, 10) {
	this->stage = 0;
	this->launching = false;
	this->ticks = 0;
	this->totalStages = 0;
};

ZoomPowerUp::~ZoomPowerUp() {

}

void ZoomPowerUp::generateObstacle() {
	int x = (GameWindow::GAME_WIDTH);

	int y = 380 - (rand() % (GameWindow::GAME_HEIGHT / 2));

	this->launching = true;

	Entity::setX(x);
	Entity::setY(y);

}

void ZoomPowerUp::handleCollision(Player* player) {
	//increment player's score
	window->getSoundMixer().playSound(window, "zoom");
	window->setScore(window->getScore() + 100);
	player->setZoom(true);
	player->setXVelocity(30);
	player->setYVelocity(0);
	player->setMortality(false);
	player->setInvTicks(200);
	destroy();
}

int ZoomPowerUp::ObstacleID(){
	return 4;
}

void ZoomPowerUp::draw(Graphics& graphics) {

	if(!launching) {
		return;
	}


	setSprite(graphics.loadImage("zoom"));


}




