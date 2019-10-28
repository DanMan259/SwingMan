#pragma once

#include <SDL.h>

#include "graphics.h"
#include "Entity.h"
#include "GameWindow.h"

using namespace std;

class GameWindow;
class Player : public Entity {
public:

	Player();

	Player(GameWindow*, int, int, SDL_Surface*);

	void gameUpdate(const float& elapsedTime);

	void gameDraw(Graphics& graphics);

	void setSwinging(const bool& swinging);

	void resetSwinging();

	Entity* getSwingingBlock() const;

private:
	GameWindow* game;

	bool dead;

	bool swinging;

	Entity* swingingBlock;
};
