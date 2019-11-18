#pragma once

#include <SDL.h>
#include <string>
#include <SDL_TTF.h>
#include <SDL_Image.h>
#include <iostream>

using namespace std;

class GraphicsText {
public:
	GraphicsText(SDL_Renderer* renderer, int fontSize, const string &text, const SDL_Color &color);

	void draw(int x, int y);

private:
	SDL_Texture* loadFont(SDL_Renderer* renderer, int fontSize, const string& message, const SDL_Color &color);

	SDL_Texture* textTexture;

	SDL_Renderer* renderer;

	SDL_Rect textRect;

};
