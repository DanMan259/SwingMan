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
	const int MAX_DISTANCE_ROPE = 130;
}

Player::Player() {
	this->game= NULL;
	this->dead = false;
	this->rope = NULL;
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
	delete(rope);
	swinging = false;
	swingingBlock = nullptr;
}


bool Player::isSwinging() const {
	return swinging;
}

Rope* Player::getRope() const {
	return rope;
}

void Player::gameUpdate(const float& elapstedTime) {

	//gravity
	if(!dead && !swinging) {
		move(0, player_constants::GRAVITY);
	}

	if(swinging) {
		rope->update();
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

void Player::startSwinging() {
	vector<Entity*> qualifiableBlocks;
	for(Entity* entity : game->getTopBlocks()) {
		int distance = entity->getX() - getX();
		if(distance < player_constants::MAX_DISTANCE_ROPE && distance > 0) {
			qualifiableBlocks.push_back(entity);
		}
	}

	if(qualifiableBlocks.empty()) {
		return;
	}

	int distance = qualifiableBlocks.at(0)->getX() - getX();
	Entity *temp;
	for(size_t i = 1; i < qualifiableBlocks.size(); i++) {
		Entity* block = qualifiableBlocks.at(i);
		int d = block->getX() - getX();

		if(d > distance) {
			temp = block;
		}
	}

	this->rope = new Rope(this, temp);
	swinging = true;
}



void Player::gameDraw(Graphics& graphics) {
	if(swinging) {
		rope->draw(graphics);
	}


	Entity::gameDraw(graphics);
}
