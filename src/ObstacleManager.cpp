#include "ObstacleManager.h"
#include "CoinObstacle.h"
#include "GeyserObstacle.h"
#include <iostream>
#include "time.h"

namespace obstacle_constants {
	const int TOTAL_OBSTACLES = 2;
}

ObstacleManager::ObstacleManager(GameWindow* window) {
	this->gameTicks = 0;
	this->window = window;
	this->obstacleTime = 20;
	this->lastObstacleTime = obstacleTime;
	srand(time(NULL));

}

void ObstacleManager::gameUpdate() {
	if(lastObstacleTime <= 0) {
		Obstacle* obstacle = getRandomObstacle();
		if(obstacle == nullptr) {
			lastObstacleTime = obstacleTime;
			return;
		}
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
	int obs = rand() % obstacle_constants::TOTAL_OBSTACLES;
	cout << obs << endl;
	switch(obs) {
	case 0:
		return new GeyserObstacle(window);
		break;
	case 1:
		return new CoinObstacle(window);
		break;
	}

	return nullptr;
}
