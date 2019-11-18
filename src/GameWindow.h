#pragma once


#include <vector>
#include "Entity.h"
#include "Graphics.h"
#include "Player.h"
#include "Rope.h"
#include "SoundMixer.h"
#include "Obstacle.h"
#include "ObstacleManager.h"
#include "GraphicsText.h"
#include <set>

using namespace std;

//forward declarations
class Player;
class Rope;
class ObstacleManager;
class Obstacle;

/*
 * This holds all of the main variables for the game. It also holds
 * the game loop. It is used for the initial startup of the sdl engine
 * and for the initial rendering of the game.
 */
class GameWindow {

public:

	/*
	 * The screen height
	 */
	static const int GAME_HEIGHT = 500;

	/*
	 * The screen width
	 */
	static const int GAME_WIDTH = 800;

	/*
	 * The game speed : how fast the map scrolls
	 */
	static const int GAME_MOVE_SPEED = 4;

	/*
	 * Default constructor
	 */
	GameWindow();

	/*
	 * Main game loop
	 * This is responsible for updating and rendering the game.
	 */
	void gameLoop();

	/*
	 * Used to handle the continuous updates of the game
	 * This is used to update the side-scrolling of all of the
	 * lava and top blocks as well as updating all other entities
	 */
	void gameUpdate(const float& elapsedTime);

	/*
	 * Used to draw all necessary items to the screen
	 */
	void gameDraw(Graphics& graphics);

	/*
	 * Called when the player falls into the lava
	 */
	void endGame();


	void restart();

	void addObstacle(Obstacle* obstacle);

	/*
	 * @return top blocks
	 */
	vector<Entity*> getTopBlocks() const;


	SoundMixer& getSoundMixer();

	/*
	 * @return lava blocks
	 */
	vector<Entity*> getLavaBlocks() const;

	vector<Obstacle*> getObstacles() const;

private:

	/*
	 * The graphics object
	 */
	int height[20];
	int heightIndex = -1;

	Graphics graphics;

	SoundMixer soundMixer;

	Player* player;

	bool finished;

	bool start;

	bool restarting;

	vector<Entity*> lavaBlocks;

	vector<Entity*> topBlocks;

	ObstacleManager* obstacleManager;

	vector<Obstacle*> obstacles;
};
