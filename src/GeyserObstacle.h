#pragma once

#include "Obstacle.h"

class GeyserObstacle : public Obstacle {
public:

	GeyserObstacle();

	GeyserObstacle(SDL_Surface* sprite);

	virtual void generateObstacle();

	virtual void draw(Graphics& graphics);

	virtual ~GeyserObstacle();

private:

	int stage;

	int ticks;

	int totalStages;

	bool created;

	bool launching;


};
