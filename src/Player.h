#pragma once

#include <SDL.h>

#include <cmath>
#include "graphics.h"
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

	bool isSwinging() const;

	Rope* getRope() const;


private:
	GameWindow* game;

	Rope* rope;

	bool dead;

	bool swinging;

	Entity* swingingBlock;
};
