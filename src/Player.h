#pragma once

#include <SDL.h>

#include "Graphics.h"
#include "Entity.h"
#include "GameWindow.h"

using namespace std;

class GameWindow;
class Rope;
class Player : public Entity {
public:

	Player();

	Player(GameWindow*, int, int, SDL_Surface*);

	void gameUpdate(const float& elapsedTime);

	void gameDraw(Graphics& graphics);

	void startSwinging();

	void resetSwinging();

	bool isFalling() const;

	bool isSwinging() const;


	Rope* getRope() const;

	void setFalling(const bool& falling);

	int getXVelocity() const;
	int getYVelocity() const;
	void setXVelocity(int value);
	void setYVelocity(int value);


private:
	GameWindow* game;
	int velocityX;
	int velocityY;
	int acc = 0;
	Rope* rope;

	bool dead;

	bool falling;

	int deathStage;

	int deathTicks;

	bool swinging;

	Entity* swingingBlock;
};
