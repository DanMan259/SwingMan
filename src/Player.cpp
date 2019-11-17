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
	this->falling = false;
	this->velocityX = 0;
	this->velocityY = 0;
	this->deathStage = 0;
	this->deathTicks = 0;


}

Player::Player(GameWindow* game, int x, int y, SDL_Surface* sprite) : Entity(x, y, sprite) {
	this->game = game;
	this->dead = false;
	this->swinging = false;
	this->falling = false;
	this->swingingBlock = nullptr;
	this->deathStage = 0;
	this->deathTicks = 0;
	this->velocityX = 0;
	this->velocityY = 0;
	this->rope = NULL;

};



void Player::resetSwinging() {
	swinging = false;
	swingingBlock = nullptr;
	delete(rope);
}


bool Player::isSwinging() const {
	return swinging;
}

Rope* Player::getRope() const {
	return rope;
}

int Player::getXVelocity() const {
	return velocityX;
}

int Player::getYVelocity() const {
	return velocityY;
}
void Player::setXVelocity(int value) {
	this->velocityX = value;

}
void Player::setYVelocity(int value) {
	this->velocityY = value;
}

void Player::gameUpdate(const float& elapstedTime) {

	//gravity

	if(dead) {
		return;
	}
	if(!dead && !swinging) {
		move(0, getYVelocity()/2.7 + (acc/2));
		acc++;
	}
	if(swinging) {
		rope->update();
		acc = 0;
	}
	//collisions
	SDL_Rect playerRect;
	playerRect.x = getX();
	playerRect.y = getY();
	playerRect.w = getWidth();
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
			game->getSoundMixer().playSound("explosion");
			dead = true;
			game->endGame();
			break;
		}
	}
	for(Obstacle* obstacle : game->getObstacles()) {
		if(!obstacle->isDestructive()) {
			continue;;
		}
		SDL_Rect entityRect;
		entityRect.x = obstacle->getX();
		entityRect.y = obstacle->getY();
		entityRect.w = obstacle->getWidth();
		entityRect.h = obstacle->getHeight();
		SDL_bool intersects = SDL_IntersectRect(&playerRect, &entityRect, &result);
		if(intersects == SDL_TRUE) {
			obstacle->handleCollision(this);
			break;
		}
	}
	for(Entity* topBlock : game->getTopBlocks()) {
			SDL_Rect entityRect;
			entityRect.x = topBlock->getX();
			entityRect.y = topBlock->getY();
			entityRect.w = topBlock->getWidth();
			entityRect.h = topBlock->getHeight();
			SDL_bool intersects = SDL_IntersectRect(&playerRect, &entityRect, &result);
			if(intersects == SDL_TRUE) {
				game->getSoundMixer().playSound("top");
				game->endGame();
				resetSwinging();
				velocityY = 0;
				falling = true;
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

bool Player::isFalling() const{
	return falling;
}

void Player::setDead(const bool& dead) {
	this->dead = dead;
}


void Player::gameDraw(Graphics& graphics) {

	if(dead) {

		if(deathTicks >= 5) {
		switch(deathStage) {
		case 0:
			move(-20, -20);
			setSprite(graphics.loadImage("explosion_1"));
			break;
		case 1:
			setSprite(graphics.loadImage("explosion_2"));
			break;
		case 2:
			setSprite(graphics.loadImage("explosion_3"));
			break;
		case 3:
			setSprite(graphics.loadImage("explosion_4"));
			break;
		case 4:
			setSprite(graphics.loadImage("explosion_5"));
			break;
		case 5:
			setSprite(graphics.loadImage("explosion_6"));
			break;
		case 6:
			setSprite(graphics.loadImage("explosion_7"));
			break;
		case 7:
			setSprite(graphics.loadImage("explosion_8"));
			break;
		default:
			setVisible(false);
			break;
		}

		deathTicks = 0;
		deathStage++;
		}

		deathTicks++;
	} else {

		if(swinging) {
			rope->draw(graphics);
		}

	}


	if(!dead) {
		if(swinging) {
			setSprite(graphics.loadImage("samurai_swinging"));
		} else {
			setSprite(graphics.loadImage("samurai_falling"));
		}
	}

	Entity::gameDraw(graphics);
}
