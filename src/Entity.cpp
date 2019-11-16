#include <SDL.h>

#include "Entity.h"
#include "Graphics.h"
#include "GameWindow.h"
#include <iostream>

using namespace std;

Entity::Entity() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->sprite = NULL;
	this->texture = NULL;
	this->visible = true;

};

Entity::Entity(int x, int y, SDL_Surface* sprite) {
	this->x = x;
	this->y = y;
	this->sprite = sprite;
	this->width = 0;
	this->height = 0;
	if(sprite != NULL) {
		this->width = sprite->w;
		this->height = sprite->h;
	}
	this->texture = NULL;
	this->visible = true;
};

Entity::Entity(const Entity& other) {
	this->x = other.x;
	this->y = other.y;
	this->width = other.width;
	this->height = other.height;
	this->sprite = other.sprite;
	this->texture = other.texture;
	this->visible = other.visible;
};

Entity::~Entity() {

}

void Entity::setSprite(SDL_Surface* sprite) {
	this->sprite = sprite;
	this->width = sprite->w;
	this->height = sprite->h;
	this->texture = NULL;
}

void Entity::setSpriteDimensions(const int &width, const int &height) {
	sprite->w = width;
	sprite->h = height;
}

void Entity::gameUpdate(const float& elapsedTime) {

}

void Entity::setVisible(const bool& visible) {
	this->visible = visible;
}

void Entity::gameDraw(Graphics& graphics) {

	if(!visible) {
		return;
	}

	if(texture == NULL) {
		texture = graphics.surfaceToTexture(sprite);
	}

	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = width;
	srcRect.h = height;
	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;
	graphics.drawSurface(texture, &srcRect, &destRect);
//	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 255, 255);
//	graphics.drawRect(&destRect);
//	SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 0);
}

SDL_Surface* Entity::getSprite() const {
	return sprite;
}

void Entity::move(const int &x, const int &y) {
	this->x = this->x + x;
	this->y = this->y + y;
}

void Entity::setY(int y) {
	this->y = y;
}

int Entity::getY() const{
	return y;
}

int Entity::getWidth() const{
	return width;
}

int Entity::getHeight() const{
	return height;
}

void Entity::setX(int x) {
	this->x = x;
}

int Entity::getX() const {
	return x;
}


bool operator==(const Entity first, const Entity other) {
 	return first.getX() == other.getX() && first.getY() == other.getY();
}

bool operator<(const Entity first, const Entity other) {
	return first.getX() < other.getX();
}
