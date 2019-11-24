#pragma once

#include <SDL.h>

#include "Graphics.h"
#include "Entity.h"
#include "GameWindow.h"

using namespace std;

//forward declarations
class GameWindow;
class Rope;

/*
 * This class is responsible for controlling the actions
 * of the player in-game
 */
class Player : public Entity {
public:

	/*
	 * Default constructor
	 */
	Player();

	/*
	 * @param window which is the game window
	 * @param x the x-coordinate of the player
	 * @param y the y-coordinate of the player
	 * @param sprite to sprite
	 */
	Player(GameWindow* window, int x , int y, SDL_Surface* sprite);

	/*
	 * Handles the updating of the player
	 */
	void gameUpdate(const float& elapsedTime);

	/*
	 * Handles the drawing of the player
	 */
	void gameDraw(Graphics& graphics);

	/*
	 * Starts the swinging sequence for player
	 */
	void startSwinging();

	/*
	 * Stops the swinging sequence for player
	 */
	void resetSwinging();

	/*
	 * @return falling
	 */
	bool isFalling() const;

	/*
	 * @return swinging
	 */
	bool isSwinging() const;

	/*
	 * @return rope
	 */
	Rope* getRope() const;

	/*
	 * Sets the falling boolean
	 */
	void setFalling(const bool& falling);

	/*
	 * Sets the dead boolean
	 */
	void setDead(const bool& dead);

	/*
	 * @return velocityX
	 */
	int getXVelocity() const;

	/*
	 * @return velocityY
	 */
	int getYVelocity() const;

	/*
	 * Sets velocity x to value
	 */
	void setXVelocity(int value);

	/*
	 * Sets velocity y to value
	 */
	void setYVelocity(int value);

	/*
	 * Sets inv ticks to value
	 */
	void setInvTicks(int value);

	/*
	 * @return game
	 */
	GameWindow* getGameWin();

	/*
	 * Sets mortality to value
	 * Determines if player dies to obstacles
	 */
	void setMortality(const bool& value);

	/*
	 * @return mortal
	 */
	bool isMortal();

	/*
	 * @return zoom
	 */
	bool isZoom();

	/*
	 * Sets the zoom to value
	 */
	void setZoom(const bool& value);


	/*
	 * @return has swung
	 */
	bool hasSwung() const;

private:

	/*
	 * The game window
	 */
	GameWindow* game;

	/*
	 * The x velocity of player
	 */
	int velocityX;

	/*
	 * The y velocity of player
	 */
	int velocityY;

	/*
	 * The acc of the player
	 */
	int acc = 0;

	/*
	 * The rope attached to player
	 */
	Rope* rope;

	/*
	 * If the player is dead
	 */
	bool dead;

	/*
	 * If player is zooming (for a power up)
	 */
	bool zoom = false;

	/*
	 * If player is mortal
	 */
	bool mortal = true;

	/*
	 * If player is falling
	 */
	bool falling;

	/*
	 * The death stage of the player
	 */
	int deathStage;

	/*
	 * If the player has finished dieing
	 */
	bool finishedDeath;

	/*
	 * The death ticks used for changing sprites
	 */
	int deathTicks;

	/*
	 * How long the player has been invicible for
	 */
	int invincibilityTicks=0;

	/*
	 * If the player is swinging on a rope
	 */
	bool swinging;


	/*
	 * If player has swung before
	 */
	bool swung;

	/*
	 * The top block the player is swinging from
	 */
	Entity* swingingBlock;
};
