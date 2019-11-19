#include "GraphicsText.h"

GraphicsText::GraphicsText(SDL_Renderer* renderer, int fontSize, const string& text, const SDL_Color& color) {
	this->renderer = renderer;
	this->textTexture = this->loadFont(renderer, fontSize, text, color);
	this->textRect.w = 30;
	this->textRect.h = 30;
	SDL_QueryTexture(this->textTexture, nullptr, nullptr, &this->textRect.w, &this->textRect.h);
}

void GraphicsText::draw(int x, int y) {
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

SDL_Texture* GraphicsText::loadFont(SDL_Renderer* renderer, int fontSize, const string& message, const SDL_Color &color) {
	TTF_Font* font = TTF_OpenFont("res/Arial.ttf", fontSize);
	if(font == nullptr) {
		cout << "Unable to load font." << endl;
		return NULL;
	}
	auto text_surface = TTF_RenderText_Solid(font, message.c_str(), color);
	if(!text_surface) {
		cout << "Unable to load text surface." << endl;
		return NULL;
	}
	auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if(!text_texture) {
		cout << "Unable to load text texture." << endl;
		return NULL;
	}

	SDL_FreeSurface(text_surface);
	return text_texture;
}



