#pragma once

#include "Obstacle.h"

class BatObstacle : public Obstacle {
public:
	/*
	 * Constructor
	 */
	BatObstacle(GameWindow* window);

	/*
	 * This method is responsible for creating lava geyser
	 */
	virtual void generateObstacle();

	/*
	 * Draws the lava geyser. Also handles all of the different stages.
	 */
	virtual void draw(Graphics& graphics);

	/*
	 * Handles collisions
	 */
	virtual void handleCollision(Player* player);

	/*
	 * Destructor
	 */
	virtual ~BatObstacle();


	void gameUpdate(const float& elapsedTime);

	virtual int ObstacleID();

private:

	bool launching;

	bool flyingSprite;

	int batTicks;
};
