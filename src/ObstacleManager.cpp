#include "ObstacleManager.h"
#include "CoinObstacle.h"
#include "BatObstacle.h"
#include "GeyserObstacle.h"
#include "ZoomPowerUp.h"
#include "InvincibilityPowerUp.h"
#include <iostream>
#include "time.h"

namespace obstacle_constants {
	const int TOTAL_OBSTACLES = 5;
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

	if(gameTicks >= 5) {
		lastObstacleTime--;
		gameTicks = 0;
	}
}


Obstacle* ObstacleManager::getRandomObstacle() {
	int obs = rand() % (obstacle_constants::TOTAL_OBSTACLES * 10);
	if(window->getDifficulty() == false){//hard
		if(obs <20)
			return new GeyserObstacle(window);
		else if(obs<25 && obs>20)
			return new CoinObstacle(window);
		else if(obs<40 && obs>25)
			return new BatObstacle(window);
		else if(obs<45 && obs>40)
			return new InvincibilityPowerUp(window);
		else if(obs<50 && obs>45)
			return new ZoomPowerUp(window);
	}else{//easy
		if(obs <15)
			return new GeyserObstacle(window);
		else if(obs<30 && obs>15)
			return new CoinObstacle(window);
		else if(obs<40 && obs>30)
			return new BatObstacle(window);
		else if(obs<47 && obs>40)
			return new InvincibilityPowerUp(window);
		else if(obs<50 && obs>47)
			return new ZoomPowerUp(window);
	}


	return nullptr;
}
