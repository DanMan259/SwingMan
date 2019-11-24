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
	this->swung = true;
	this->finishedDeath = false;


}

Player::Player(GameWindow* game, int x, int y, SDL_Surface* sprite) : Entity(x, y, sprite) {
	this->game = game;
	this->dead = false;
	this->swinging = false;
	this->falling = false;
	this->swingingBlock = nullptr;
	this->deathStage = 0;
	this->deathTicks = 0;
	this->swung = false;
	this->velocityX = 0;
	this->velocityY = 0;
	this->rope = NULL;
	this->finishedDeath = false;


};



void Player::resetSwinging() {
	swinging = false;
	swingingBlock = nullptr;
	delete(rope);
	rope = nullptr;
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
GameWindow* Player::getGameWin(){
	return this->game;
}

void Player::gameUpdate(const float& elapstedTime) {

	//gravity

	if(dead) {
		return;
	}

	if(!dead && !swinging) {
		if(isZoom()==false){
			move(0, getYVelocity()/2.7 + (acc/2));
			acc++;
		}
	}
	if(isZoom()==false){
		if(swinging) {
			rope->update();
			acc = 0;
		}
	}

	//collisions
	SDL_Rect playerRect;
	playerRect.x = getX();
	playerRect.y = getY();
	playerRect.w = getWidth();
	playerRect.h = getHeight();
	SDL_Rect result;
	for(Entity* lavaBlock : game->getLavaBlocks()) {
		if(lavaBlock == nullptr) {
			continue;
		}
		SDL_Rect entityRect;
		entityRect.x = lavaBlock->getX();
		entityRect.y = lavaBlock->getY();
		entityRect.w = lavaBlock->getWidth();
		entityRect.h = lavaBlock->getHeight();
		SDL_bool intersects = SDL_IntersectRect(&playerRect, &entityRect, &result);
		if(intersects == SDL_TRUE) {
			game->getSoundMixer().playSound(this->getGameWin(), "explosion");

			dead = true;
			game->endGame();

			break;
		}
	}
	for(Obstacle* obstacle : game->getObstacles()) {
		if(obstacle == nullptr) {
				continue;
		}
		if(!obstacle->isDestructive()) {
			continue;
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
			if(topBlock == nullptr) {
				continue;
			}
			SDL_Rect entityRect;
			entityRect.x = topBlock->getX();
			entityRect.y = topBlock->getY();
			entityRect.w = topBlock->getWidth();
			entityRect.h = topBlock->getHeight();
			SDL_bool intersects = SDL_IntersectRect(&playerRect, &entityRect, &result);
			if(intersects == SDL_TRUE && !falling) {

				game->getSoundMixer().playSound(this->getGameWin(), "top");
				resetSwinging();
				velocityY = 0;

				game->endGame();
				falling = true;

				break;
			}
		}
}

void Player::setFalling(const bool& falling) {
	this->falling = falling;
}

void Player::startSwinging() {
	if(zoom) {
		return;
	}
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
	swung = true;
}

bool Player::hasSwung() const {
	return swung;
}

bool Player::isFalling() const{
	return falling;
}

void Player::setDead(const bool& dead) {
	this->dead = dead;
}

void Player::setMortality(const bool& value){
	this->mortal = value;
}

bool Player::isMortal(){
	return this->mortal;
}

void Player::setInvTicks(int value){
	this->invincibilityTicks = value;
}

bool Player::isZoom(){
	return zoom;
}

void Player::setZoom(const bool& value){
	this->zoom = value;
}

void Player::gameDraw(Graphics& graphics) {

	if(finishedDeath) {
		return;
	}

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
			finishedDeath = true;
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
	if(isMortal() == false){
		if(invincibilityTicks>400){
			setMortality(true);
			invincibilityTicks=0;
			if(isZoom() == true){
				this->setXVelocity(this->getXVelocity()/3);
				this->setYVelocity(-15);

				setZoom(false);
				setMortality(false);
				invincibilityTicks=350;
			}

		}
		else{

			invincibilityTicks++;
		}
	}


	if(!dead) {
		if(swinging) {
			if(isMortal())
				setSprite(graphics.loadImage("samurai_swinging"));
			else
				if(isZoom())
					setSprite(graphics.loadImage("samurai_zooming"));
				else
					setSprite(graphics.loadImage("invincible_swinging"));

		} else {
			if(isMortal())
				setSprite(graphics.loadImage("samurai_falling"));
			else
				if(isZoom())
					setSprite(graphics.loadImage("samurai_zooming"));
				else
					setSprite(graphics.loadImage("invincible_falling"));

		}
	}

	Entity::gameDraw(graphics);
}
