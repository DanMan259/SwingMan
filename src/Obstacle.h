#pragma once

#include "Entity.h"


class Obstacle : public Entity {

public:
	Obstacle(int x, int y, SDL_Surface* sprite, int time);

	void gameUpdate(const float& elapsedTime);

	void gameDraw(Graphics& graphics);

private:

	int time;

	int gameTicks;

	int lastObstacleTime;


};
