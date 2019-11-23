#include "GeyserObstacle.h"
#include "Obstacle.h"
#include "GameWindow.h"
#include "time.h"
#include "Entity.h"
#include <iostream>

#include <cmath>



GeyserObstacle::GeyserObstacle(GameWindow* window) : Obstacle(window, 0, 0, NULL, false, 50) {
	this->stage = 0;
	this->launching = false;
	this->ticks = 0;
	this->totalStages = 0;

};

GeyserObstacle::~GeyserObstacle() {

}

void GeyserObstacle::generateObstacle() {
	int x = (GameWindow::GAME_WIDTH);

	window->getSoundMixer().playSound("geyser");

	int y = 380;

	this->launching = true;

	Entity::setX(x);
	Entity::setY(y);

}

void GeyserObstacle::handleCollision(Player* player) {
	if(player->isMortal()){
		window->getSoundMixer().playSound("explosion");
		player->setDead(true);
		window->endGame();
	}
}

int GeyserObstacle::ObstacleID(){
	return 1;
}


void GeyserObstacle::draw(Graphics& graphics) {

	if(!launching) {
		return;
	}

	if(ticks >= 2) {
		switch(stage) {
		case 0:
			setSprite(graphics.loadImage("explosion_1"));
			break;
		case 1:
			setSprite(graphics.loadImage("explosion_2"));
			break;
		case 2:
			setSprite(graphics.loadImage("explosion_3"));
			break;
		case 3:
			setSprite(graphics.loadImage("explosion_4"));
			break;
		case 4:
			setSprite(graphics.loadImage("explosion_5"));
			break;
		case 5:
			setSprite(graphics.loadImage("explosion_6"));
			break;
		case 6:
			setSprite(graphics.loadImage("explosion_7"));
			break;
		case 7:
			setSprite(graphics.loadImage("explosion_8"));
			Entity::move(0, -115);
			destructive = true;
			break;
		case 8:
			setSprite(graphics.loadImage("geyser_4"));
			break;
		case 9:
			setSprite(graphics.loadImage("geyser_3"));
			break;
		case 10:
			setSprite(graphics.loadImage("geyser_2"));
			if(totalStages < 50) {
				stage = 8;
				totalStages++;
			} else {
				totalStages = 0;
			}
			break;
		case 11:
			setSprite(graphics.loadImage("geyser_5"));
			break;
		case 12:
			setSprite(graphics.loadImage("geyser_6"));
			destructive = false;
			break;
		case 13:
			setSprite(graphics.loadImage("geyser_7"));
			break;
		case 14:
			setSprite(graphics.loadImage("geyser_8"));
			destroy();
			break;
		}

		stage++;
		ticks = 0;
	}
	ticks++;
}

