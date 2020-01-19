#include "CoinObstacle.h"
#include "Obstacle.h"
#include "GameWindow.h"
#include "time.h"
#include "Entity.h"
#include <iostream>

#include <cmath>

//Create the coin object
CoinObstacle::CoinObstacle(GameWindow* window) : Obstacle(window, 0, 0, NULL, true, 10) {
	this->stage = 0;
	this->launching = false;
	this->ticks = 0;
	this->totalStages = 0;
};

CoinObstacle::~CoinObstacle() {

}

//Generate the coin location
void CoinObstacle::generateObstacle() {
  	//Start coin at edge of screen
	int x = (GameWindow::GAME_WIDTH);
	//Random y location
	int y = 380 - (rand() % (GameWindow::GAME_HEIGHT / 2));

	this->launching = true;

	Entity::setX(x);
	Entity::setY(y);

}
int CoinObstacle::ObstacleID(){
	return 2;
}

//Deal with collision between coin and player
void CoinObstacle::handleCollision(Player* player) {
	//increment player's score
	window->setScore(window->getScore() + 100);
  	//Play coin sound
	window->getSoundMixer().playSound(window, "coin");
	destroy();
}

//Display the coin
void CoinObstacle::draw(Graphics& graphics) {

	if(!launching) {
		return;
	}
	
  	//Animate spinning coin with multiple sprite images
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
}




