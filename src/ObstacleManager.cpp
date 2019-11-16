#include "ObstacleManager.h"
#include "GeyserObstacle.h"
#include "time.h"

ObstacleManager::ObstacleManager(GameWindow* window) {
	this->gameTicks = 0;
	this->window = window;
	this->obstacleTime = 30;
	this->lastObstacleTime = obstacleTime;
	srand(time(NULL));
}

void ObstacleManager::gameUpdate() {
	if(lastObstacleTime <= 0) {
		Obstacle* obstacle = getRandomObstacle();
		window->addObstacle(obstacle);
		obstacle->generateObstacle();
		lastObstacleTime = obstacleTime;
	}

	gameTicks++;

	if(gameTicks >= 10) {
		lastObstacleTime--;
		gameTicks = 0;
	}
}


Obstacle* ObstacleManager::getRandomObstacle() {
	return new GeyserObstacle();
}
