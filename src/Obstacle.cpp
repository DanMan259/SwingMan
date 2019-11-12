#include "Obstacle.h"
#include "Entity.h"
#include "SDL.h"


Obstacle::Obstacle(int x, int y, SDL_Surface* sprite, int time) : Entity(x, y, sprite) {
	this->time = time;
	this->lastObstacleTime = 0;
	this->gameTicks = 0;
};

void Obstacle::gameDraw(Graphics& graphics) {

}

void Obstacle::gameUpdate(const float& elapsedTime) {
	if(lastObstacleTime <= 0) {
		//generate an obstacle
		lastObstacleTime = time;
	}

	gameTicks++;

	if(gameTicks >= 10) {
		lastObstacleTime--;
		gameTicks = 0;
	}

}




