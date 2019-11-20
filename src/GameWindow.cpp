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

	pauseContinueText = nullptr;
	pauseNewGameText = nullptr;
	endGameText = nullptr;
	endNewGameText = nullptr;
	endScoreGameText = nullptr;

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



	state = GameState::START;

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
					state = GameState::IN_GAME;
				}

				if (event.key.keysym.sym == SDLK_m) {
					state = (state == GameState::PAUSE ? GameState::IN_GAME : GameState::PAUSE);
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
	delete(pauseContinueText);
	delete(pauseNewGameText);

	delete(endGameText);
	delete(endNewGameText);
	delete(endScoreGameText);
	player = nullptr;
	obstacleManager = nullptr;
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
		topBlock = nullptr;
	}
	for(Entity* lavaBlock : lavaBlocks) {
		delete(lavaBlock);
		lavaBlock = nullptr;
	}
	for(Entity* obstacle : obstacles) {
		delete(obstacle);
		obstacle = nullptr;
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
	state = GameState::END;
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

	switch(state) {
	case GameState::PAUSE:
	{
		break;
	}
	case GameState::END:
	{
		//player->gameUpdate(elapsedTime);
		break;
	}
	case GameState::START:
	{
		break;
	}
	case GameState::IN_GAME:
	{
		cout << "a" << endl;
			player->gameUpdate(elapsedTime);

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
					entity = nullptr;
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
					entity = nullptr;
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
					entity = nullptr;
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
		break;
	}
	}


}

void GameWindow::gameDraw(Graphics &graphics) {

	graphics.clear();

	switch(state) {
	case START:
	{
		break;
	}
	case END:
	{

		if(endGameText == nullptr) {
			SDL_Color color = {255,255,255};
			endGameText = new GraphicsText(graphics.getRenderer(), 70, "res/AGENCYB.TTF", "Game Over", color);
		}

		if(endScoreGameText == nullptr) {

			SDL_Color color = {255,255,255};

			char output_str[40];
			char score_str[25];
			itoa(gamescore, score_str, 10);
			strcpy(output_str, "Score: ");
			strcat(output_str, score_str);


			endScoreGameText = new GraphicsText(graphics.getRenderer(), 60, "res/AGENCYB.TTF", output_str, color);

		}

		if(endNewGameText == nullptr) {
			SDL_Color color = {255,0,0};
			endNewGameText = new GraphicsText(graphics.getRenderer(), 40, "res/AGENCYB.TTF", "Press A to Play Again!", color);
		}

		endScoreGameText->draw(290, 240);
		endNewGameText->draw(240, 330);
		endGameText->draw(255, 120);

		break;
	}
	case IN_GAME:
	{
		GraphicsText score(graphics.getRenderer(), 30, "res/Arial.ttf", to_string(gamescore), {255, 255, 255, 255});
		score.draw(10, GAME_HEIGHT/2);
		break;
	}
	case PAUSE:
	{
		if(this->pauseNewGameText == nullptr) {
			SDL_Color color = {255,255,255};
			pauseNewGameText = new GraphicsText(graphics.getRenderer(), 70, "res/AGENCYB.TTF", "(N)ew Game", color);
		}

		if(this->pauseContinueText == nullptr) {
			SDL_Color color = {255,255,255};
			pauseContinueText = new GraphicsText(graphics.getRenderer(), 70, "res/AGENCYB.TTF", "(C)ontinue Game", color);
		}

		pauseNewGameText->draw(255, 140);
		pauseContinueText->draw(190, 240);
		break;
	}
	}


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

	player->gameDraw(graphics);

	graphics.flip();

}
