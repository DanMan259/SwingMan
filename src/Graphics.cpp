#include <SDL.h>
#include <SDL_Mixer.h>
#include <SDL_Image.h>
#include <SDL_TTF.h>
#include <iostream>

#include "Graphics.h"
#include "GameWindow.h"

using namespace std;

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(GameWindow::GAME_WIDTH, GameWindow::GAME_HEIGHT, 0, &this->window, &this->renderer);
	SDL_SetWindowTitle(this->window, "SwingingMan");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);

}

void Graphics::drawLine(const int &x1, const int &y1, const int &x2, const int &y2) const {
	SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2);
}

void Graphics::putImage(const string &name, const string &path) {
	if (sprites.count(path) == 0) {
		sprites[name] = IMG_Load(path.c_str());
	}
}

SDL_Surface* Graphics::loadImage(const string &name) {
	return sprites[name];
}

SDL_Texture* Graphics::surfaceToTexture(SDL_Surface* &surface) {
	return SDL_CreateTextureFromSurface(renderer, surface);
}


void Graphics::drawSurface(SDL_Texture* &source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	SDL_RenderCopy(this->renderer, source, sourceRectangle, destinationRectangle);
}

void Graphics::drawRect(const SDL_Rect &rect) const {
	SDL_RenderDrawRect(this->renderer, &rect);
}

void Graphics::drawFilledRect(const SDL_Rect &rect) const {
	SDL_RenderFillRect(this->renderer, &rect);
}

void Graphics::flip() {
	SDL_RenderPresent(this->renderer);
}

void Graphics::clear() {
	SDL_RenderClear(this->renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return renderer;
}
