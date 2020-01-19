
#pragma once

#include <SDL.h>
#include <string>
#include <map>

using namespace std;

struct SDL_Window;
struct SDL_Renderer;

/*
 * The Graphics class is responsible for holding
 * the renderer for putting images onto the screen
 */
class Graphics {
public:

	/*
	 * Default constructor
	 */
	Graphics();

	/*
	 * Destructor
	 */
	~Graphics();

	/*
	 * @param name of how the sprite will be accessed
	 * @param path of the sprite
	 */
	void putImage(const string &name, const string& path);

	/*
	 * @param name the image wanted to be loaded
	 *
	 * Creates a SDL Surface of an image
	 */
	SDL_Surface* loadImage(const string &name);

	/*
	 * @param surface which a texture will be created from
	 */
	SDL_Texture* surfaceToTexture(SDL_Surface* &surface);

	/*
	 * Draws a line
	 *
	 * @param x1 and y1 which is the first coordinate
	 * @param x2 and y2 which is the second coordinate
	 */
	void drawLine(const int &x1, const int &y1, const int &x2, const int &y2) const;

	/*
	 * @param source which is the texture
	 * @param sourceRectangle which is the source rectangle
	 * @param destinationRectangle which is the destination rectangle
	 */
	void drawSurface(SDL_Texture* &source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/*
	 * @param rect which is the rectangle wanted to be drawn
	 */
	void drawRect(const SDL_Rect &rect) const;

	/*
	 * @param rect which is the rectangle wanted to be drawn and filled
	 */
	void drawFilledRect(const SDL_Rect &rect) const;


	/*
	 * FLips renderer
	 */
	void flip();

	/*
	 * Clears renderer
	 */
	void clear();

	/*
	 * @return renderer
	 */
	SDL_Renderer* getRenderer() const;

private:

	/*
	 * The window of the game
	 */
	SDL_Window * window;

	/*
	 * The renderer
	 */
	SDL_Renderer* renderer;

	/*
	 * The sprites map
	 */
	map<string, SDL_Surface*> sprites;


};
