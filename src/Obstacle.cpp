#include "Obstacle.h"
#include "Entity.h"
#include "SDL.h"
#include <iostream>


Obstacle::Obstacle() {
	Entity();
	this->destroyed = false;
	this->destructive = false;
	this->hitboxOffset = 0;
}
Obstacle::Obstacle(int x, int y, SDL_Surface* sprite, bool destructive, int hitboxOffset) : Entity(x, y, sprite) {
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

int Obstacle::getHitboxOffset() const {
	return hitboxOffset;
}

void Obstacle::gameUpdate(const float& elapsedTime) {

}




