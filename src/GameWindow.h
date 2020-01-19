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
#include "HighScore.h"
#include <set>

using namespace std;

//forward declarations
class Player;
class Rope;
class ObstacleManager;
class Obstacle;
class GraphicsText;
class SoundMixer;


enum GameState {
	START, CONTROLS, IN_GAME, END, PAUSE, SETTINGS
};

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


	/*
	 * @param graphics the graphics rendering class
	 * Restarts the game
	 */
	void restart(Graphics& graphics);

	/*
	 * @param obstacle which is the obstacle to be added to the game
	 */
	void addObstacle(Obstacle* obstacle);

	/*
	 * @param score to the score
	 */
	void setScore(const int& score);

	/*
	 * @return score
	 */
	int getScore() const;

	/*
	 * @return difficulty
	 */
	bool getDifficulty() const;

	/*
	 * @return top blocks
	 */
	vector<Entity*> getTopBlocks() const;


	/*
	 * @return soundMixer
	 */
	SoundMixer& getSoundMixer();

	/*
	 * @return lava blocks
	 */
	vector<Entity*> getLavaBlocks() const;

	/*
	 * @return obstacles vector list
	 */
	vector<Obstacle*> getObstacles() const;

	/*
	 * @return state
	 */
	GameState getGameState() const;

	/*
	 * @return soundMuted
	 */
	bool isSoundMuted() const;


private:

	/*
	 * Height used for the map
	 */
	int height[28];

	/*
	 * Height index of the height array
	 */
	int heightIndex = -1;

	/*
	 * The gamescore
	 */
	int gamescore = 0;

	/*
	 * The graphics object
	 */
	Graphics graphics;

	/*
	 * The sound mixer object
	 */
	SoundMixer* soundMixer;

	/*
	 * The player object
	 */
	Player* player;

	/*
	 * If game is finished
	 */
	bool finished;

	/*
	 * If game is restarting
	 */
	bool restarting;

	/*
	 * A font in the game
	 */
	TTF_Font *font;

	/*
	 * If music is muted
	 */
	bool muteMusic;

	/*
	 * If the sound is muted
	 */
	bool muteSound;

	/*
	 * The difficulty of the game
	 */
	bool difficulty;

	/*
	 * The state of the game
	 */
	GameState state;

	/*
	 * The highscore object
	 */
	HighScore* highscore;

	/*
	 * Holds lava blocks in the game
	 */
	vector<Entity*> lavaBlocks;

	/*
	 * Holds top blocks in the game
	 */
	vector<Entity*> topBlocks;

	/*
	 * Holds obstacle manager object
	 */
	ObstacleManager* obstacleManager;

	/*
	 * Holds all the obstacles curently in the game
	 */
	vector<Obstacle*> obstacles;

	/*
	 * The pause continue text
	 */
	GraphicsText* pauseContinueText;

	/*
	 * The pause new game text
	 */
	GraphicsText* pauseNewGameText;

	/*
	 * The end new game text
	 */
	GraphicsText* endNewGameText;

	/*
	 * The end score game text
	 */
	GraphicsText* endScoreGameText;

	/*
	 * The end high score game text
	 */
	GraphicsText* endHighScoreGameText;

	/*
	 * The end game text
	 */
	GraphicsText* endGameText;

	/*
	 * The title game text
	 */
	GraphicsText* titleGameText;

	/*
	 * The start game text
	 */
	GraphicsText* startGameText;

	/*
	 * The controls game text
	 */
	GraphicsText* controlsGameText;

	/*
	 * The controls back text
	 */
	GraphicsText* controlsBackText;

	/*
	 * The controls swing text
	 */
	GraphicsText* controlsSwingText;

	/*
	 * The controls pause text
	 */
	GraphicsText* controlsPauseText;

	/*
	 * The start settings text
	 */
	GraphicsText* startSettingsText;

	/*
	 * The score text
	 */
	GraphicsText* score;

	/*
	 * The music settings text
	 */
	GraphicsText* musicSettingsText;

	/*
	 * The sound settings text
	 */
	GraphicsText* soundSettingsText;

	/*
	 * The difficulty settings text
	 */
	GraphicsText* difficultySettingsText;

	/*
	 * The start screen settings text
	 */
	GraphicsText* startScreenSettingsText;


};
