#pragma once

#include "Graphics.h"

/*
 * Loads all of the sprites in spriteLoader.txt into game
 */
class SpriteLoader {

public:

	/*
	 * @param graphics which is the graphics object whee sprites will be placed
	 */
	SpriteLoader(Graphics& graphics);

	/*
	 * Reads spriteLoader.txt file
	 */
	void initiliaze(Graphics& graphics);
};
