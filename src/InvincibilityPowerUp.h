#pragma once

#include "SDL_Mixer.h"
#include "Obstacle.h"


/*
 * This is a specific game powerup that extends
 * the Obstacle abstract class
 *
 * This obstacle is a powerup, that gives the player invincibility for some time
 */
class InvincibilityPowerUp : public Obstacle {
public:

	/*
	 * Constructor
	 */
	InvincibilityPowerUp(GameWindow* window);

	/*
	 * This method is responsible for creating coin
	 */
	virtual void generateObstacle();

	/*
	 * Draws the coin. Also handles all of the different stages.
	 */
	virtual void draw(Graphics& graphics);

	/*
	 * Handles collisions
	 */
	virtual void handleCollision(Player* player);

	/*
	 * Destructor
	 */
	virtual ~InvincibilityPowerUp();

	virtual int ObstacleID();

private:

	/*
	 * The stage of the obstacle
	 */
	int stage;

	/*
	 * The ticks
	 */
	int ticks;

	/*
	 * The total stages
	 */
	int totalStages;

	/*
	 * If obstacle is launching
	 */
	bool launching;


};
