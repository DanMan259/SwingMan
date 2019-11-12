#pragma once

#include <SDL.h>

#include "graphics.h"

/*
 * The entity object is responsible for each item in the game
 * that holds a position and a sprite. Examples of this can be the
 * lava blocks, or the staglemites. The player will also be considered
 * an entity in this case.
 *
 * @author Daniel Tavernese
 */
class Entity {

public:

	/** Default Constructor */
	Entity();

	/*
	 * @param x the entity x position
	 * @param y the entity y position
	 * @param sprite the sprite of the entity
	 */
	Entity(int x, int y, SDL_Surface* sprite);

	/*
	 * Copy constructor
	 * @param copy which is what this object will copy from
	 */
	Entity(const Entity& copy);

	//Destructor used for taking stuff off the heap
	~Entity();

	/*
	 * This method is responsible for handling all of the
	 * continuous updates on the entity. These can be changes
	 * in position, different sprite states etc.
	 */
	void gameUpdate(const float& elapsedTime);

	/*
	 * Draws the entity onto the screen
	 * @graphics which holds the renderer object
	 */
	void gameDraw(Graphics& graphics);

	void setSprite(SDL_Surface* sprite);

	/*
	 * Allows for a dynamic change of the sprite width and heigh
	 * @param width is the new width
	 * @param height is the new height
	 */
	void setSpriteDimensions(const int &width, const int &height);

	/*
	 * This will move the entity from it's current position to an
	 * offset position
	 * @param x is the x offset
	 * @param y is the y offset
	 */
	void move(const int &x, const int &y);

	/*
	 * Changes the entity y coordinate
	 * @param y is the new y coordinate
	 */
	void setY(int y);

	/*
	 * @return the entity y coordinate
	 */
	int getY() const;

	/*
	 * Changes the entity x coordinate
	 * @param x is the new x coordinate
	 */
	void setX(int x);

	void setVisible(const bool& visible);

	/*
	 * @return the entity x coordinate
	 */
	int getX() const;

	/*
	 * @return the entity sprite
	 */
	SDL_Surface* getSprite() const;

	/*
	 * @return the entity height
	 */
	int getHeight() const;

	/*
	 * @return the entity width
	 */
	int getWidth() const;

private:

	/*
	 * The entity sprite
	 */
	SDL_Surface *sprite;

	/*
	 * The entity texture
	 */
	SDL_Texture *texture;

	/*
	 * The entity width
	 */
	int width;

	/*
	 * The entity height
	 */
	int height;

	/*
	 * The entity x-coordinate
	 */
	int x;

	/*
	 * The entity y-coordinate
	 */
	int y;

	bool visible;
};

	/*
	 * Overloading == option
	 */
	bool operator==(const Entity first, const Entity other);


	/*
	 * Overloading < option
	 */
	bool operator<(const Entity first, const Entity other);
