#include <SDL.h>
#include <SDL_Mixer.h>
#include <SDL_TTF.h>
#include <SDL_TTF.h>

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

	if(TTF_Init()==-1) {
			printf("TTF_Init: %s\n", TTF_GetError());
			exit(-1);
		}

		font = TTF_OpenFont("./res/AGENCYB.TTF",64);
		if(font == NULL)
		{
		   fprintf(stderr,"font open failure %s\n",SDL_GetError());
		   exit(-1);
		}

	gameLoop();
}

void GameWindow::gameLoop() {
	srand(time(NULL));
	Graphics graphics;
	this->soundMixer = SoundMixer();
	SDL_Event event;
	SpriteLoader spriteLoader(graphics);

	obstacleManager = nullptr;
	start_flag = false;
	finished = false;
	menu_flag = false;

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



	player = new Player(this, 200, 150, graphics.loadImage("samurai_falling"));


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
									obstacleManager = new ObstacleManager(this);
									start_flag = true;
									finished = false;
								} else if (event.key.keysym.sym == SDLK_m) {
									if(menu_flag == false)
										this->menu_flag = true;
									else
										this->menu_flag = false;
								}

				if(event.key.keysym.sym == SDLK_r) {
					if(finished) {
						restart();
					}
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

	TTF_Quit();
	delete(obstacleManager);
	delete(player);
}


void GameWindow::setScore(const int& score) {
	this->gamescore = score;
}

int GameWindow::getScore() const {
	return gamescore;
}

void GameWindow::restart() {
	for(Entity* topBlock : topBlocks) {
		delete(topBlock);
	}
	for(Entity* lavaBlock : lavaBlocks) {
		delete(lavaBlock);
	}
	for(Entity* obstacle : obstacles) {
		delete(obstacle);
	}
	this->topBlocks.clear();
	this->lavaBlocks.clear();
	this->obstacles.clear();

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

	player = new Player(this, 200, 150, graphics.loadImage("samurai_falling"));
	obstacleManager = new ObstacleManager(this);
	finished = false;
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


	if(start_flag) {
		player->gameUpdate(elapsedTime);
	}

	if (menu_flag) {
		return;
	}

	if (finished) {
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

			gamescore++;
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

	if(obstacleManager != nullptr) {
		obstacleManager->gameUpdate();
	}

}

void GameWindow::gameDraw(Graphics &graphics) {

	SDL_Color color;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	if(menu_flag) {
			color = {255,255,255};
			SDL_Surface *textSurf = TTF_RenderText_Solid(font,"(N)ew Game",color);
			srcRect.x = 0; srcRect.y = 0; srcRect.w = 300; srcRect.h = 100;
			destRect.x = 255; destRect.y = 120; destRect.w = 250; destRect.h = 80;
			graphics.drawSurface(graphics.surfaceToTexture(textSurf), &srcRect, &destRect);

			textSurf = TTF_RenderText_Solid(font,"(C)ontinue",color);
			srcRect.x = 0; srcRect.y = 0; srcRect.w = 300; srcRect.h = 100;
			destRect.x = 255; destRect.y = 220; destRect.w = 250; destRect.h = 80;
			graphics.drawSurface(graphics.surfaceToTexture(textSurf), &srcRect, &destRect);
			graphics.flip();
			return;
		}

	graphics.clear();

	GraphicsText score(graphics.getRenderer(), 30, to_string(gamescore), {255, 255, 255, 255});

	score.draw(10, GAME_HEIGHT/2);

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

	if(start_flag) {
		player->gameDraw(graphics);

	}

	if(finished) {
			color = {255,255,255};
			SDL_Surface *endTextSurf = TTF_RenderText_Solid(font,"Game Over",color);
			srcRect.x = 0; srcRect.y = 0; srcRect.w = 250; srcRect.h = 100;
			destRect.x = 255; destRect.y = 120; destRect.w = 250; destRect.h = 100;
			graphics.drawSurface(graphics.surfaceToTexture(endTextSurf), &srcRect, &destRect);


			char output_str[40];
			char score_str[25];
			itoa(gamescore, score_str, 10);
			strcpy(output_str, "Score: ");
			strcat(output_str, score_str);

			color = {188,188,188};
			SDL_Surface *scoreTextSurf = TTF_RenderText_Solid(font,output_str,color);
			srcRect.x = 0; srcRect.y = 0; srcRect.w = 500; srcRect.h = 70;
			destRect.x = 285; destRect.y = 260; destRect.w = 180; destRect.h = 50;
			graphics.drawSurface(graphics.surfaceToTexture(scoreTextSurf), &srcRect, &destRect);

			color = {255,0,0};
			SDL_Surface *againTextSurf = TTF_RenderText_Solid(font,"Press Button A to play again!",color);
			srcRect.x = 0; srcRect.y = 0; srcRect.w = 500; srcRect.h = 100;
			destRect.x = 225; destRect.y = 350; destRect.w = 300; destRect.h = 40;
			graphics.drawSurface(graphics.surfaceToTexture(againTextSurf), &srcRect, &destRect);

	}

	graphics.flip();
}
