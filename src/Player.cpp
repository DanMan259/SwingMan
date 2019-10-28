/*
 * Player.cpp
 *
 *  Created on: Oct. 25, 2019
 *      Author: Dan_t
 */
#include "Player.h"
#include "SDL.h"
#include <iostream>

namespace player_constants {
	const int GRAVITY = 4;
}

Player::Player() {
	this->game= NULL;
	this->dead = false;
	this->swinging = false;
	this->swingingBlock = nullptr;
}

Player::Player(GameWindow* game, int x, int y, SDL_Surface* sprite) : Entity(x, y, sprite) {
	this->game = game;
	this->dead = false;
	this->swinging = false;
	this->swingingBlock = nullptr;
};


void Player::resetSwinging() {
	swinging = false;
	swingingBlock = nullptr;
}

Entity* Player::getSwingingBlock() const {
	return swingingBlock;
}


void Player::gameUpdate(const float& elapstedTime) {

	//gravity
	if(!dead && !swinging) {
		move(0, player_constants::GRAVITY);
	}
	//collisions
	SDL_Rect playerRect;
	playerRect.x = getX();
	playerRect.y = getY();
	playerRect.w= getWidth();
	playerRect.h = getHeight();
	SDL_Rect result;
	for(Entity* lavaBlock : game->getLavaBlocks()) {
		SDL_Rect entityRect;
		entityRect.x = lavaBlock->getX();
		entityRect.y = lavaBlock->getY();
		entityRect.w = lavaBlock->getWidth();
		entityRect.h = lavaBlock->getHeight();
		SDL_bool intersects = SDL_IntersectRect(&playerRect, &entityRect, &result);
		if(intersects == SDL_TRUE) {
			dead = true;
			game->endGame();
		}
	}
}

void Player::setSwinging(const bool& swinging) {
	this->swinging = swinging;
}



void Player::gameDraw(Graphics& graphics) {
	if(swinging) {

		if(swingingBlock == nullptr) {
			int x = -1;
		for(Entity* entity : game->getTopBlocks()) {
			int distance = entity->getX() - getX();
			if(distance > 0) {
				if(x == -1 || distance < x) { //look at this
					x = distance;
					swingingBlock = entity;
					}
				}
			}
		}


		SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 255, 255);
		graphics.drawLine(getX() + getWidth(), getY(), swingingBlock->getX(), swingingBlock->getY() + swingingBlock->getHeight());
		SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 0);
	}


	Entity::gameDraw(graphics);
}



