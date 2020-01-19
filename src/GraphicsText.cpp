#include "GraphicsText.h"

GraphicsText::GraphicsText(SDL_Renderer* renderer, int fontSize, const string& font, const string& text, const SDL_Color& color) {
	this->renderer = renderer;
	this->textTexture = this->loadFont(renderer, fontSize, font, text, color);
	this->textRect.w = 30;
	this->textRect.h = 30;
	SDL_QueryTexture(this->textTexture, nullptr, nullptr, &this->textRect.w, &this->textRect.h);
}

GraphicsText::~GraphicsText() {
	//cout << "a" << endl;
	if(textTexture != nullptr) {
		SDL_DestroyTexture(this->textTexture);
	}
}

void GraphicsText::draw(int x, int y) {
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

int GraphicsText::getW(){
	return this->textRect.w;
}

SDL_Texture* GraphicsText::loadFont(SDL_Renderer* renderer, int fontSize, const string& f, const string& message, const SDL_Color &color) {

	TTF_Font* font = TTF_OpenFont(f.c_str(), fontSize);
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

	TTF_CloseFont(font);
	SDL_FreeSurface(text_surface);
	return text_texture;
}



