#include "GeyserObstacle.h"
#include "Obstacle.h"
#include "GameWindow.h"
#include "time.h"
#include "Entity.h"

#include <cmath>



GeyserObstacle::GeyserObstacle() : Obstacle() {
	srand(time(NULL));
	this->stage = 0;
	this->launching = false;
	this->ticks = 0;
	this->totalStages = 0;
	this->created = false;

};
GeyserObstacle::GeyserObstacle(SDL_Surface* sprite): Obstacle(0, 0, sprite, 10) {
	srand(time(NULL));
	this->stage = 0;
	this->launching = false;
	this->ticks = 0;
	this->totalStages = 0;
	this->created = false;

}

GeyserObstacle::~GeyserObstacle() {

}

void GeyserObstacle::generateObstacle() {
	int x = (GameWindow::GAME_WIDTH/2) + (rand() % GameWindow::GAME_WIDTH/2);
	int y = 380;

	this->launching = true;
	this->created = true;

	Entity::setX(x);
	Entity::setY(y);


}


void GeyserObstacle::draw(Graphics& graphics) {
	if(ticks >= 5) {
		if(launching) {
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
				stage = 0;
				totalStages++;
				if(totalStages >= 5) {
					launching = false;
				}
				break;
			}

			stage++;
			ticks = 0;
		} else {

			switch(stage) {
			case 0:
				setSprite(graphics.loadImage("geyser_4"));
				break;
			case 1:
				setSprite(graphics.loadImage("geyser_3"));
				break;
			case 2:
				setSprite(graphics.loadImage("geyser_2"));
				stage = 0;
				setVisible(false);
				break;
			}

			stage++;
			ticks = 0;
		}
	}

	ticks++;

	if(created) {
		Entity::gameDraw(graphics);
	}

}

