#pragma once

#include "SDL_Mixer.h"
#include "Obstacle.h"


/*
 * This is a specific game obstacle that extends
 * the Obstacle abstract class
 *
 * This obstacle is a lava geyser, that the player
 * must dodge or else they will incinerate
 */
class CoinObstacle : public Obstacle {
public:

	/*
	 * Constructor
	 */
	CoinObstacle(GameWindow* window);

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
	virtual ~CoinObstacle();

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
