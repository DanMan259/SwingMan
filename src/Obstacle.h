#pragma once

#include "Entity.h"


class Obstacle : public Entity {

public:

	Obstacle();

	Obstacle(int x, int y, SDL_Surface* sprite, int obstacleTime);

	virtual ~Obstacle();

	void gameUpdate(const float& elapsedTime);

	void gameDraw(Graphics& graphics);

	virtual void generateObstacle() = 0;

	virtual void draw(Graphics& graphics) = 0;


private:

	int obstacleTime;

	int gameTicks;

	int lastObstacleTime;


};
