#pragma once

#include <vector>
#include "Obstacle.h"
#include "GameWindow.h"

//forward declarations
class GameWindow;
class Obstacle;

/*
 * This class is responsible for generating obstacles as the
 * player goes through the game
 */
class ObstacleManager {

public:

	/*
	 * The constructor
	 * @param window which is the game window
	 */
	ObstacleManager(GameWindow* window);

	/*
	 * This method will check if a new obstacle
	 * should be added to the game
	 */
	void gameUpdate();

	/*
	 * This method will generate a random obstacle
	 * NOT COMPLETE. Right now it only returns lava geyser
	 */
	Obstacle* getRandomObstacle();

private:

	/*
	 * The obstacle time
	 */
	int obstacleTime;

	/*
	 * The game ticks
	 */
	int gameTicks;

	/*
	 * The last obstacle time
	 */
	int lastObstacleTime;

	/*
	 * The game window
	 */
	GameWindow* window;
};
