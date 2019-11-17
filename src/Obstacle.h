#pragma once

#include "Entity.h"
#include "Player.h"
#include "GameWindow.h"

//forward declarations
class GameWindow;
class Player;

/*
 * This abstract class will be extended by obstacles in the game
 * to create individual obstacles
 */
class Obstacle : public Entity {

public:

	/*
	 * The default constructor
	 */
	Obstacle();

	/*
	 * @param x the initial x coordinate of obstacle
	 * @param y the initial y coordinate of obstacle
	 * @param sprite the obstacle sprite
	 * @param destructive
	 * @param hitBoxOffset, makes the hitbox of the obstacle feel correct
	 */
	Obstacle(GameWindow* window, int x, int y, SDL_Surface* sprite, bool destructive, int hitboxOffset);

	/*
	 * Destructor
	 */
	virtual ~Obstacle();

	/*
	 * Obstacle uploaded frequently
	 */
	void gameUpdate(const float& elapsedTime);

	/*
	 * Responsible for drawing obstacle
	 */
	void gameDraw(Graphics& graphics);

	/*
	 * Destroys obstacle
	 */
	void destroy();

	/*
	 * @return destroyed
	 */
	bool isDestroyed() const;

	/*
	 * @return hitBoxOffset
	 */
	int getHitboxOffset() const;

	/*
	 * @return destructive
	 */
	bool isDestructive() const;

	/*
	 * @return window
	 */
	GameWindow* getWindow() const;

	/*
	 * virtual method all obstacles must implement this
	 */
	virtual void generateObstacle() = 0;

	/*
	 * virtual method all obstacles must implement this
	 */
	virtual void draw(Graphics& graphics) = 0;


	/*
	 * Handles collisions
	 */
	virtual void handleCollision(Player* player) = 0;

protected:

	/*
	 * If when the player hits the obstacle should
	 * they be destroyed
	 */
	bool destructive;

	/*
	 * Holds game window
	 */
	GameWindow* window;

private:

	/*
	 * The hitbox offset
	 */
	int hitboxOffset;

	/*
	 * If the obstacle is being destroyed
	 */
	bool destroyed;



};
