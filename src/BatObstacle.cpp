#include "BatObstacle.h"
#include "time.h"


//Initialize bat object
BatObstacle::BatObstacle(GameWindow* window) : Obstacle(window, 0, 0, NULL, true, 50) {
	this->batTicks = 0;
	this->flyingSprite = false;
	this->launching = false;
};

BatObstacle::~BatObstacle() {

}

//Generate random y location and start bat at edge of screen
void BatObstacle::generateObstacle() {
	srand(time(NULL));
	int x = (GameWindow::GAME_WIDTH);
	
	int y = 120 + (rand() % (GameWindow::GAME_HEIGHT / 4));
	
  	//Play bat sound
	window->getSoundMixer().playSound(window, "bat");

	this->launching = true;

	Entity::setX(x);
	Entity::setY(y);

}

//Handle collisions between bat and player
void BatObstacle::handleCollision(Player* player) {
	if(!player->isFalling()) {
		if(player->isMortal()){
			//Play collision sound
			window->getSoundMixer().playSound(window, "top");
          	//Reset rope swing
			player->resetSwinging();
          	//Stop the player from moving
			player->setYVelocity(0);
          	//Make the player fall
			player->setFalling(true);
          	//End the game
			window->endGame();
		}
	}
}

//Display the bat
void BatObstacle::draw(Graphics& graphics) {
  	//Animate the bat flying using multiple sprites
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
}

int BatObstacle::ObstacleID(){
	return 0;
}


