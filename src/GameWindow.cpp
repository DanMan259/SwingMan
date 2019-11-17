#include <SDL.h>
#include <SDL_Mixer.h>

#include <iostream>

#include "GameWindow.h"
#include "SpriteLoader.h"
#include "Graphics.h"
#include "Entity.h"
#include "Time.h"
#include "Player.h"
#include "Rope.h"
#include "GeyserObstacle.h"
#include "Obstacle.h"
#include <cmath>
#include <vector>

//h
using namespace std;

const int FPS = 50;
const int MAX_FRAME_TIME = 1000 / FPS;

int topPattern[81];
int topPatternIndex;

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
	this->soundMixer = SoundMixer();
	SDL_Event event;
	SpriteLoader spriteLoader(graphics);
	obstacleManager = new ObstacleManager(this);

	start = false;

	topPatternIndex = 0;
	for(int i = 0; i < 81; i++) {
		int offset = 3;
		if(i < 30) {
			topPattern[i] = i * offset;
		} else if(i >= 30 && i < 50) {
			topPattern[i] = topPattern[29] + (rand() % 2);
		} else {
			topPattern[i] = topPattern[29] - ((i-50) * offset);
		}
	}

	SDL_Surface *blockSurface = graphics.loadImage("block");
	for (int i = 0; i < 25; i++) {
		Entity *block = new Entity(i * 40, 380, blockSurface);
		block->setY(block->getY() + 10 * 5);
		lavaBlocks.push_back(block);
	}

	SDL_Surface *topBlockSurface = graphics.loadImage("big_grey_block");
	for (int i = 0; i < 25; i++) {
		Entity *block = new Entity(i * 40, 0, topBlockSurface);

		block->setY(block->getY() - 10 * (rand() % 10));
		topBlocks.push_back(block);
	}

//testing different top widths
//	for (int i = 0; i < 81; i++) {
//		Entity *block = new Entity(i * 10, -topBlockSurface->h, topBlockSurface);
//		block->setY(block->getY() + topPattern[i]);
//		cout << block->getY() + topPattern[i] << endl;
//
//		topBlocks.push_back(block);
//	}



	Player plyr = Player(this, 200, 150, graphics.loadImage("samurai_falling"));

	player = &plyr;

	//obstacles.push_back(obs);





	//Rope rpe = Rope(player);
	//rope = &rpe;

	//rope->initiliaze(100, 100);
	int LAST_UPDATE_TIME = SDL_GetTicks();

	while (true) {

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_SPACE) {
					if(!player->isSwinging() && !player->isFalling()) {
						player->startSwinging();
					}
				}
				if(event.key.keysym.sym == SDLK_a) {
					start = true;
				}
			} else if (event.type == SDL_KEYUP) {

				if (event.key.keysym.sym == SDLK_SPACE) {
					if(!player->isFalling()) {
					player->resetSwinging();
					}
				}

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
	delete(obstacleManager);
}

vector<Entity*> GameWindow::getLavaBlocks() const {
	return lavaBlocks;
}

vector<Entity*> GameWindow::getTopBlocks() const {
	return topBlocks;
}

vector<Obstacle*> GameWindow::getObstacles() const {
	return obstacles;
}

void GameWindow::addObstacle(Obstacle* obstacle) {
	obstacles.push_back(obstacle);
}

SoundMixer& GameWindow::getSoundMixer() {
	return soundMixer;
}

void GameWindow::gameUpdate(const float &elapsedTime) {


	if(start) {
		player->gameUpdate(elapsedTime);
	}

	if (finished) {
		//TTF_init();
		return;
	}

	for (size_t i = 0; i < lavaBlocks.size(); i++) {
		Entity *entity = lavaBlocks.at(i);
		if (entity->getX() <= -40) {
			lavaBlocks.erase(lavaBlocks.begin() + i);
			Entity *block = new Entity(
					lavaBlocks.at(lavaBlocks.size() - 1)->getX() + 40, 380,
					entity->getSprite());
			if(heightIndex >= 20 || heightIndex == -1){
				double divider = (double(rand()%2)+2);
				for(int j = 0; j<20; j++){
					height[j] = int(5.0*sin(double(j) / divider)+5.0);
				}
				heightIndex = 0;
			}


			block->setY(block->getY() + 10 * 5);//height[heightIndex++]);
			delete (entity);
			lavaBlocks.push_back(block);
			continue;
		} else {

			entity->setX(entity->getX() - player->getXVelocity());
		}

	}

	for (size_t i = 0; i < topBlocks.size(); i++) {
		Entity *entity = topBlocks.at(i);

		if (entity->getX() <= -120) {
			if (player->isSwinging()) {
				if(entity == player->getRope()->getSwingingBlock()) {
				player->resetSwinging();
				}
			}
			topBlocks.erase(topBlocks.begin() + i);

			Entity *block = new Entity(
					topBlocks.at(topBlocks.size() - 1)->getX()
							+ entity->getWidth(), 0, entity->getSprite());
			block->setY(block->getY() - 10 * (10-height[heightIndex++]));
			topBlocks.push_back(block);
			delete (entity);

			continue;
		} else {

			entity->setX(entity->getX() - player->getXVelocity());

		}
	}

	for (size_t i = 0; i < obstacles.size(); i++) {
		Obstacle *entity = obstacles.at(i);
		if(entity->isDestroyed()) {
			obstacles.erase(obstacles.begin() + i);
			delete(entity);
			cout << "destroy obstacle" << endl;
		}
	}

	for (size_t i = 0; i < obstacles.size(); i++) {
		Obstacle *entity = obstacles.at(i);
		entity->setX(entity->getX() - player->getXVelocity());
		entity->gameUpdate(elapsedTime);
	}

	obstacleManager->gameUpdate();

}

void GameWindow::gameDraw(Graphics &graphics) {


	graphics.clear();

	for (Entity *lavaBlock : lavaBlocks) {
		lavaBlock->gameDraw(graphics);
	}

	for (Entity *topBlock : topBlocks) {
		topBlock->gameDraw(graphics);
	}

	for (Obstacle *obs : obstacles) {
		if(!obs->isDestroyed()) {
		obs->gameDraw(graphics);
		}
	}

	if(start) {
		player->gameDraw(graphics);

	}

	graphics.flip();
}
