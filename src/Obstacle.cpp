#include "Obstacle.h"
#include "Entity.h"
#include "SDL.h"


Obstacle::Obstacle() {
	Entity();
	this->obstacleTime = 0;
	this->lastObstacleTime = 0;
	this->gameTicks = 0;
}
Obstacle::Obstacle(int x, int y, SDL_Surface* sprite, int obstacleTime) : Entity(x, y, sprite) {
	this->obstacleTime = obstacleTime;
	this->lastObstacleTime = 0;
	this->gameTicks = 0;
};

Obstacle::~Obstacle() {

}

void Obstacle::gameDraw(Graphics& graphics) {
	draw(graphics);
}

void Obstacle::gameUpdate(const float& elapsedTime) {
	if(lastObstacleTime <= 0) {
		generateObstacle();
		lastObstacleTime = obstacleTime;
	}

	gameTicks++;

	if(gameTicks >= 10) {
		lastObstacleTime--;
		gameTicks = 0;
	}

}




