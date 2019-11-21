#include "BatObstacle.h"
#include "time.h"


BatObstacle::BatObstacle(GameWindow* window) : Obstacle(window, 0, 0, NULL, true, 50) {
	this->batTicks = 0;
	this->flyingSprite = false;
	this->launching = false;
};

BatObstacle::~BatObstacle() {

}

void BatObstacle::generateObstacle() {
	srand(time(NULL));
	int x = (GameWindow::GAME_WIDTH);

	int y = 120 + (rand() % (GameWindow::GAME_HEIGHT / 8));

	window->getSoundMixer().playSound("bat");



	this->launching = true;

	Entity::setX(x);
	Entity::setY(y);

}

void BatObstacle::handleCollision(Player* player) {
	if(!player->isFalling()) {
		window->getSoundMixer().playSound("top");
		if(player->isMortal()){
			player->resetSwinging();
			player->setYVelocity(0);
			player->setFalling(true);
			window->endGame();
		}
	}
}

void BatObstacle::draw(Graphics& graphics) {



	if(batTicks >= 10) {
		if(flyingSprite) {
			setSprite(graphics.loadImage("bat2"));
		} else {
			setSprite(graphics.loadImage("bat1"));
		}
		flyingSprite = !flyingSprite;
		batTicks = 0;
	}

	batTicks++;

	Entity::gameDraw(graphics);
}






