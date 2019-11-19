#include "CoinObstacle.h"
#include "Obstacle.h"
#include "GameWindow.h"
#include "time.h"
#include "Entity.h"
#include <iostream>

#include <cmath>


CoinObstacle::CoinObstacle(GameWindow* window) : Obstacle(window, 0, 0, NULL, true, 10) {
	this->stage = 0;
	this->launching = false;
	this->ticks = 0;
	this->totalStages = 0;
};

CoinObstacle::~CoinObstacle() {

}

void CoinObstacle::generateObstacle() {
	int x = (GameWindow::GAME_WIDTH);

	int y = 380 - (rand() % (GameWindow::GAME_HEIGHT / 2));

	this->launching = true;

	Entity::setX(x);
	Entity::setY(y);

}

void CoinObstacle::handleCollision(Player* player) {
	//increment player's score
	window->setScore(window->getScore() + 100);
	window->getSoundMixer().playSound("coin");
	destroy();
}


void CoinObstacle::draw(Graphics& graphics) {

	if(!launching) {
		return;
	}

	if(ticks >= 2) {
		switch(stage) {
		case 0:
			setSprite(graphics.loadImage("coin_1"));
			break;
		case 1:
			setSprite(graphics.loadImage("coin_2"));
			break;
		case 2:
			setSprite(graphics.loadImage("coin_3"));
			break;
		case 3:
			setSprite(graphics.loadImage("coin_4"));
			stage = 0;
			break;
		}

		stage++;
		ticks = 0;
	}
	ticks++;
	Entity::gameDraw(graphics);
}





