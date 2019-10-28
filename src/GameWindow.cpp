#include <SDL.h>

#include <iostream>

#include "GameWindow.h"
#include "SpriteLoader.h"
#include "Graphics.h"
#include "Entity.h"
#include "Time.h"
#include "Player.h"
#include <vector>

using namespace std;

const int FPS = 50;
const int MAX_FRAME_TIME = 1000 / FPS;

int main(int argv, char **args) {
	GameWindow game;
	return 0;
}

GameWindow::GameWindow() {
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

void GameWindow::gameLoop() {
	srand(time(NULL));
	Graphics graphics;
	SDL_Event event;
	SpriteLoader spriteLoader(graphics);

	SDL_Surface *blockSurface = graphics.loadImage("block");
	for (int i = 0; i < 21; i++) {
		Entity *block = new Entity(i * 40, 380, blockSurface);
		block->setY(block->getY() + 10 * (rand() % 10));
		lavaBlocks.push_back(block);
	}

	SDL_Surface *topBlockSurface = graphics.loadImage("brown_block");
	for (int i = 0; i < 21; i++) {
		Entity *block = new Entity(i * 40, 0, topBlockSurface);
		block->setY(block->getY() - 10 * (rand() % 10));
		topBlocks.push_back(block);
	}

	Player plyr = Player(this, 100, 100, graphics.loadImage("player"));
	player = &plyr;

	Rope rpe = Rope(player);
	rope = &rpe;

	rope->initiliaze(100, 100);
	int LAST_UPDATE_TIME = SDL_GetTicks();

	while (true) {

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_SPACE) {
					cout << "a" << endl;
					player->setSwinging(true);
				}
			} else if (event.type == SDL_KEYUP) {
			} else if (event.type == SDL_QUIT) {
				return;
			}
		}

		const int CURRENT_TIME_MS = SDL_GetTicks(); // start

		int start = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->graphics = graphics;
		this->gameUpdate(min(ELAPSED_TIME_MS, MAX_FRAME_TIME));

		LAST_UPDATE_TIME = CURRENT_TIME_MS;
		this->gameDraw(graphics);

		int end = SDL_GetTicks();

		SDL_Delay(MAX_FRAME_TIME - (end - start));

	}
}

void GameWindow::endGame() {
	this->finished = true;
}

vector<Entity*> GameWindow::getLavaBlocks() const {
	return lavaBlocks;
}

vector<Entity*> GameWindow::getTopBlocks() const {
	return topBlocks;
}

void GameWindow::gameUpdate(const float &elapsedTime) {

	if (finished) {
		//TTF_init();
		return;
	}

	player->gameUpdate(elapsedTime);

	for (size_t i = 0; i < lavaBlocks.size(); i++) {
		Entity *entity = lavaBlocks.at(i);

		if (entity->getX() <= -40) {
			lavaBlocks.erase(lavaBlocks.begin() + i);
			Entity *block = new Entity(
					lavaBlocks.at(lavaBlocks.size() - 1)->getX() + 40, 380,
					entity->getSprite());
			block->setY(block->getY() + 10 * (rand() % 10));
			delete (entity);
			lavaBlocks.push_back(block);
			continue;
		} else {

			entity->setX(entity->getX() - GAME_MOVE_SPEED);
		}

	}

	for (size_t i = 0; i < topBlocks.size(); i++) {
		Entity *entity = topBlocks.at(i);

		if (entity->getX() <= -40) {
			if (entity == player->getSwingingBlock()) {
				player->resetSwinging();
			}
			cout << entity->getX() << endl;
			topBlocks.erase(topBlocks.begin() + i);
			Entity *block = new Entity(
					topBlocks.at(topBlocks.size() - 1)->getX()
							+ entity->getWidth(), 0, entity->getSprite());
			block->setY(block->getY() - 10 * (rand() % 10));
			delete (entity);
			topBlocks.push_back(block);
			continue;
		} else {

			entity->setX(entity->getX() - GAME_MOVE_SPEED);
		}

	}
}

void GameWindow::gameDraw(Graphics &graphics) {

	if (finished) {
		return;
	}

	graphics.clear();

	for (Entity *lavaBlock : lavaBlocks) {
		lavaBlock->gameDraw(graphics);
	}

	for (Entity *topBlock : topBlocks) {
		topBlock->gameDraw(graphics);
	}

	player->gameDraw(graphics);

	rope->draw(graphics);

	graphics.flip();
}

