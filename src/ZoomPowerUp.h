#pragma once

#include "SDL_Mixer.h"
#include "Obstacle.h"


/*
 * This is a specific game powerup that extends
 * the Obstacle abstract class
 *
 * This obstacle is a powerup, that gives the player invincibility and speeds them up for some time
 */
class ZoomPowerUp : public Obstacle {
public:

	/*
	 * Constructor
	 */
	ZoomPowerUp(GameWindow* window);

	/*
	 * This method is responsible for creating zoom obstacle
	 */
	virtual void generateObstacle();

	/*
	 * Draws the zoom obstacle. Also handles all of the different stages.
	 */
	virtual void draw(Graphics& graphics);

	/*
	 * Handles collisions
	 */
	virtual void handleCollision(Player* player);

	/*
	 * Destructor
	 */
	virtual ~ZoomPowerUp();

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
