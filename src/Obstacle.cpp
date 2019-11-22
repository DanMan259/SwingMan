#include "Obstacle.h"
#include "Entity.h"
#include "SDL.h"
#include <iostream>


Obstacle::Obstacle() {
	Entity();
	this->window = nullptr;
	this->destroyed = false;
	this->destructive = false;
	this->hitboxOffset = 0;
}
Obstacle::Obstacle(GameWindow* window, int x, int y, SDL_Surface* sprite, bool destructive, int hitboxOffset) : Entity(x, y, sprite) {
	this->window = window;
	this->destroyed = false;
	this->destructive = destructive;
	this->hitboxOffset = hitboxOffset;
};

Obstacle::~Obstacle() {

}

void Obstacle::gameDraw(Graphics& graphics) {
	draw(graphics);
}

void Obstacle::destroy() {
	destroyed = true;
}

bool Obstacle::isDestroyed() const {
	return destroyed;
}

bool Obstacle::isDestructive() const {
	return destructive;
}

GameWindow* Obstacle::getWindow() const {
	return window;
}

int Obstacle::getHitboxOffset() const {
	return hitboxOffset;
}

void Obstacle::gameUpdate(const float& elapsedTime) {

}

int Obstacle::ObstacleID(){
	return -1;
}



