#include <SDL.h>
#include <SDL_Mixer.h>
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


	restarting = false;

	controlsBackText = nullptr;
	controlsSwingText = nullptr;
	controlsPauseText = nullptr;
	startGameText = nullptr;
	pauseContinueText = nullptr;
	pauseNewGameText = nullptr;
	endGameText = nullptr;
	titleGameText = nullptr;
	endNewGameText = nullptr;
	endScoreGameText = nullptr;
	controlsGameText = nullptr;
	score = nullptr;

	SDL_Surface *blockSurface = graphics.loadImage("block");
	for (int i = 0; i < 25; i++) {
		Entity *block = new Entity(i * 40, 380, blockSurface);
		block->setY(block->getY() + 10 * 5);
		lavaBlocks.push_back(block);
	}
	if(heightIndex == -1){
		double divider = (double(rand()%2)+2);
		for(int j = 0; j<28; j++){
			height[j] = int(5.0*sin(double(j) / divider)+5.0);
		}
		heightIndex = 0;
	}

	SDL_Surface *topBlockSurface = graphics.loadImage("gravel_texture");
	for (int i = 0; i < 28; i++) {
		Entity *block = new Entity(i * 40, 0, topBlockSurface);

		block->setY(block->getY() - 10 * height[i]);//(rand() % 10));
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
				if(event.key.keysym.sym == SDLK_s) {
					if(state == GameState::START) {
						restart(graphics);
					}
					if(state == GameState::CONTROLS) {
						state = GameState::START;
					}
				}
				if(event.key.keysym.sym == SDLK_g) {
				if(state == GameState::PAUSE) {
						state = GameState::START;
					}
				}

				if (event.key.keysym.sym == SDLK_m) {
					if(state == GameState::IN_GAME) {
						state = GameState::PAUSE;
					}
				}

				if(event.key.keysym.sym == SDLK_c) {
					if(state == GameState::START) {
						state = GameState::CONTROLS;
					}
					if(state == GameState::PAUSE) {
						state = GameState::IN_GAME;
					}
				}

				if(event.key.keysym.sym == SDLK_a) {
					if(state == GameState::END) {
						restart(graphics);
					}
				}



			} else if (event.type == SDL_KEYUP) {

				if (event.key.keysym.sym == SDLK_SPACE) {
					if(!player->isFalling()) {
					player->resetSwinging();
					}
				}

			} else if (event.type == SDL_QUIT) {
				cout << "AB" << endl;

					TTF_Quit();
					delete(controlsBackText);
					delete(controlsSwingText);
					delete(controlsPauseText);
					delete(obstacleManager);
					delete(player);
					delete(pauseContinueText);
					delete(pauseNewGameText);
					delete(startGameText);
					delete(endGameText);
					delete(endNewGameText);
					delete(endScoreGameText);
					delete(controlsGameText);
					delete(titleGameText);
					delete(score);
					player = nullptr;
					obstacleManager = nullptr;
					//cout << "A" << endl;
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

		int sleepTime = (MAX_FRAME_TIME - (end - start));

		if(sleepTime > 0) {
			SDL_Delay(sleepTime);
		}

	}


}


void GameWindow::setScore(const int& score) {
	this->gamescore = score;
}

int GameWindow::getScore() const {
	return gamescore;
}

void GameWindow::restart(Graphics& graphics) {


	restarting = true;


	for(Obstacle* obstacle : this->obstacles) {
		obstacle->destroy();
	}

	controlsBackText = nullptr;
	controlsSwingText = nullptr;
	controlsPauseText = nullptr;
	startGameText = nullptr;
	pauseContinueText = nullptr;
	pauseNewGameText = nullptr;
	endGameText = nullptr;
	endNewGameText = nullptr;
	endScoreGameText = nullptr;
	controlsGameText = nullptr;
	titleGameText = nullptr;
	score = nullptr;

	player = new Player(this, 200, 150, graphics.loadImage("samurai_falling"));
	obstacleManager = new ObstacleManager(this);
	state = GameState::IN_GAME;

	gamescore = 0;

	restarting = false;
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

	if(restarting) {
		return;
	}


	switch(state) {
	case GameState::PAUSE:
	{
		break;
	}
	case GameState::CONTROLS:
	{
		break;
	}
	case GameState::END:
	{
		player->gameUpdate(elapsedTime);
		break;
	}
	case GameState::START:
	{
		break;
	}
	case GameState::IN_GAME:
	{
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

				if (entity->getX() <= -240) {
					if (player->isSwinging()) {
						if(entity == player->getRope()->getSwingingBlock()) {
						player->resetSwinging();
						}
					}
					topBlocks.erase(topBlocks.begin() + i);

					if(state == GameState::IN_GAME) {
						gamescore++;
					}
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
					//cout << "destroy obstacle" << endl;
				}
			}

			for (size_t i = 0; i < obstacles.size(); i++) {
				Obstacle *entity = obstacles.at(i);
				entity->setX(entity->getX() - player->getXVelocity());
				entity->gameUpdate(elapsedTime);
			}

			if(obstacleManager != nullptr) {
				if(state == GameState::IN_GAME) {
				obstacleManager->gameUpdate();
				}
			}

			player->gameUpdate(elapsedTime);

		break;
	}
	}


}

void GameWindow::gameDraw(Graphics &graphics) {

	if(restarting) {
		return;
	}


	graphics.clear();

	for (Entity *lavaBlock : lavaBlocks) {
			lavaBlock->gameDraw(graphics);
		}

		for (Entity *topBlock : topBlocks) {
			topBlock->gameDraw(graphics);
		}

		for (Obstacle *obs : obstacles) {
			if(!obs->isDestroyed()) {
				if(state != GameState::START && state != GameState::CONTROLS) {
			obs->gameDraw(graphics);
				}
			}
		}

		if(state != GameState::START && state != GameState::CONTROLS) {
			player->gameDraw(graphics);
		}

	switch(state) {
	case START:
	{

		if(this->titleGameText == nullptr) {
			titleGameText = new GraphicsText(graphics.getRenderer(), 60, "res/AGENCYB.TTF", "SWING MAN!", {255,0,0});

		}
		if(this->startGameText == nullptr) {
			startGameText = new GraphicsText(graphics.getRenderer(), 50, "res/AGENCYB.TTF", "Press (S) To Start Game!", {255, 255, 255, 255});
		}

		if(this->controlsGameText == nullptr) {
			controlsGameText = new GraphicsText(graphics.getRenderer(), 30, "res/AGENCYB.TTF", "Press (C) For Game Controls", {255, 255, 255, 255});
		}

		titleGameText->draw(260, 150);
		startGameText->draw(180, 260);
		controlsGameText->draw(250, 340);
		break;
	}
	case CONTROLS:
	{
		if(this->controlsSwingText == nullptr) {
			controlsSwingText = new GraphicsText(graphics.getRenderer(), 30, "res/AGENCYB.TTF", "To Swing Hold Spacebar And To Let Go Release Spacebar", {255,255,255,255});

		}
		if(this->controlsPauseText == nullptr) {
			controlsPauseText = new GraphicsText(graphics.getRenderer(), 30, "res/AGENCYB.TTF", "To Open Up Pause Menu Press (M)", {255, 255, 255, 255});
		}

		if(this->controlsBackText == nullptr) {
			controlsBackText = new GraphicsText(graphics.getRenderer(), 30, "res/AGENCYB.TTF", "Press (S) To Go Back To Start Screen", {255, 0, 0});
		}

		controlsSwingText->draw(120, 200);
		controlsPauseText->draw(220, 250);
		controlsBackText->draw(200, 350);
	}
	break;
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

		endScoreGameText->draw(295, 240);
		endNewGameText->draw(240, 330);
		endGameText->draw(260, 120);

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
		if(this->score == nullptr) {
			score = new GraphicsText(graphics.getRenderer(), 30, "res/Arial.ttf", to_string(gamescore), {255, 255, 255, 255});
		}

		if(this->pauseNewGameText == nullptr) {
			SDL_Color color = {255,255,255};
			pauseNewGameText = new GraphicsText(graphics.getRenderer(), 70, "res/AGENCYB.TTF", "(G)o Back To Start Screen", color);
		}

		if(this->pauseContinueText == nullptr) {
			SDL_Color color = {255,255,255};
			pauseContinueText = new GraphicsText(graphics.getRenderer(), 70, "res/AGENCYB.TTF", "(C)ontinue Game", color);
		}

		score->draw(10, GAME_HEIGHT/2);
		pauseNewGameText->draw(100, 140);
		pauseContinueText->draw(190, 240);
		break;
	}
	}



	graphics.flip();

}
