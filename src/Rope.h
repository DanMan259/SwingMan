#pragma once

#include "Player.h"


class Player;
class Rope {
public:

	/*
	 * @param window which is the game window
	 * @param x the x-coordinate of the player
	 * @param y the y-coordinate of the player
	 * @param sprite to sprite
	 */
	Rope(Player* attached, Entity *swingingBlock);
	/*
	 * Handles the initialization of a new rope
	 */

	void initiliaze(int x, int y);
	/*
	 * Handles the updating of the rope
	 */
	void update();
	/*
	 * Handles the drawing of the rope
	 */
	void draw(Graphics& graphics);

	/*
	 * Returns the ceiling block that the rope is attached to
	 */
	Entity* getSwingingBlock() const;


private:
	/*
	 * reference to the player that is attached to the rope
	 */
	Player* attached;
	/*
	 * the X vector from the attached ceiling block to the player
	 */
	double vectorX;
	/*
	 * the Y vector from the attached ceiling block to the player
	 */
	double vectorY;
	/*
	 * The length of the rope
	 */
	double length;
	/*
	 * The angle between the rope and the X axis when the rope is initialized
	 */
	double initAngle;
	/*
	 * The angular frequency of the swinging motion
	 */
	double angularFreq;
	/*
	 * A time variable used to keep track of how long the player has been attached to the rope so far, this resets everytime the player
	 * lets go of the rope
	 */
	double time;
	/*
	 * the sdl_tick time when the player attaches to the rope, this is used to calculate the time variable
	 */
	int ropeStart;
	/*
	 * Reference to the ceiling block that the rope is attached to
	 */
	Entity* swingingBlock;

};
