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
#include "BatObstacle.h"
#include <cmath>
#include <vector>

//h
using namespace std;

const int FPS = 50;
const int MAX_FRAME_TIME = 1000 / FPS;

int topPattern[81];
int topPatternIndex;

int menu_dot_position_y[] = {235, 295, 355};
int menu_position_index = 0;

int pause_menu_dot_position_y[] = {200, 270};
int pause_position_index = 0;

int settings_menu_dot_position_y[] = {150, 220, 290, 360};
int settings_position_index = 0;

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
	this->soundMixer = new SoundMixer();
	SDL_Event event;
	SpriteLoader spriteLoader(graphics);


	obstacleManager = nullptr;
	finished = false;
	muteMusic = false;
	muteSound = false;
	difficulty = true;

	restarting = false;

	controlsBackText = nullptr;
	controlsSwingText = nullptr;
	controlsPauseText = nullptr;
	startGameText = nullptr;
	pauseContinueText = nullptr;
	musicSettingsText = nullptr;
	startScreenSettingsText = nullptr;
	soundSettingsText = nullptr;
	difficultySettingsText = nullptr;
	startSettingsText = nullptr;
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
					if(state == GameState::IN_GAME) {
						if(!player->isSwinging() && !player->isFalling()) {
							player->startSwinging();
						}
					}
				}

				if(event.key.keysym.sym == SDLK_DOWN) {
					if(state == GameState::START) {
						menu_position_index = (menu_position_index + 1) % 3;
					}
					if(state == GameState::PAUSE) {
						pause_position_index = (pause_position_index + 1) % 2;
					}
					if(state == GameState::SETTINGS) {
						settings_position_index = (settings_position_index + 1) % 4;
					}
				}

				if(event.key.keysym.sym == SDLK_RETURN) {
					if(state == GameState::START) {
						switch(menu_position_index % 3) {
						case 0:
							//start
							restart(graphics);
							soundMixer->playSound(this, "button");
							break;
						case 1:
							//controls
							state = GameState::CONTROLS;
							menu_position_index = 0;
							soundMixer->playSound(this, "button");
							break;
						case 2:
							//settings
							state = GameState::SETTINGS;
							menu_position_index = 0;
							soundMixer->playSound(this, "button");
							break;
						}

						continue;
					}
						if(state == GameState::PAUSE) {
							switch(pause_position_index % 2) {
							case 0:
								//start
								state = GameState::IN_GAME;
								soundMixer->playSound(this, "button");
								break;
							case 1:
								//controls
								state = GameState::START;
								soundMixer->playSound(this, "button");
								menu_position_index = 0;
								break;
							}
							continue;
					}

						if(state == GameState::SETTINGS) {
							switch(settings_position_index % 4) {
							case 0:
								//start
								soundMixer->muteMusic(muteMusic ? false : true);
								muteMusic = !muteMusic;
								musicSettingsText = nullptr;
								soundMixer->playSound(this, "button");
								break;
							case 1:
								soundMixer->playSound(this, "button");
								muteSound = !muteSound;
								soundSettingsText = nullptr;

								//controls
								break;
							case 2:
								cout<<"difficulty";
								soundMixer->playSound(this, "button");
								difficulty=!difficulty;
								difficultySettingsText = nullptr;

								break;

							case 3:
								state = GameState::START;
								settings_position_index = 0;
								soundMixer->playSound(this, "button");

								break;
							}


							continue;
						}
				}

				if(event.key.keysym.sym == SDLK_UP) {
					if(state == GameState::START) {
						if(menu_position_index == 0) {
							menu_position_index = 2;
						} else {
							menu_position_index = (menu_position_index - 1) % 3;
						}
					}

					if(state == GameState::PAUSE) {
						if(pause_position_index == 0) {
							pause_position_index = 1;
						} else {
							pause_position_index = (pause_position_index - 1) % 2;
						}
					}

					if(state == GameState::SETTINGS) {
						if(settings_position_index == 0) {
							settings_position_index = 3;
						} else {
							settings_position_index = (settings_position_index - 1) % 4;
						}
					}
				}
				if(event.key.keysym.sym == SDLK_s) {
					if(state == GameState::CONTROLS) {
						state = GameState::START;
						soundMixer->playSound(this, "button");
					}
				}


				if (event.key.keysym.sym == SDLK_m) {
					if(state == GameState::IN_GAME) {
						pause_position_index = 0;
						state = GameState::PAUSE;
						soundMixer->playSound(this, "button");
					}
				}



				if(event.key.keysym.sym == SDLK_a) {
					if(state == GameState::END) {
						restart(graphics);
						soundMixer->playSound(this, "button");
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
					delete(musicSettingsText);
					delete(startScreenSettingsText);
					delete(soundSettingsText);
					delete(difficultySettingsText);
					delete(this->startSettingsText);
					delete(pauseNewGameText);
					delete(startGameText);
					delete(soundMixer);
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


GameState GameWindow::getGameState() const {
	return state;
}
void GameWindow::setScore(const int& score) {
	this->gamescore = score;
}

int GameWindow::getScore() const {
	return gamescore;
}

bool GameWindow::getDifficulty() const{
	return difficulty;
}
bool GameWindow::isSoundMuted() const {
	return this->muteSound;
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
	musicSettingsText = nullptr;
	startScreenSettingsText = nullptr;
	soundSettingsText = nullptr;
	difficultySettingsText = nullptr;
	endScoreGameText = nullptr;
	startSettingsText = nullptr;
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
	return *soundMixer;
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
	case GameState::SETTINGS:
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

					if(state == GameState::IN_GAME && player->hasSwung()) {
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

				if(entity->ObstacleID() == 0){
					//if we want to make the game much much harder

					if(heightIndex == 28){
						heightIndex = 0;
					}
					if(difficulty == false){
						if(player->getY() < entity->getY()){
							entity->setY(entity->getY() - 1);

						}
						else if(player->getY() > entity->getY()){
							entity->setY(entity->getY() + 1);
						}
					}

					entity->setY(entity->getY() + (this->height[heightIndex]-5)/4);
				}
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
				if(state != GameState::START && state != GameState::CONTROLS && state != GameState::SETTINGS) {
			obs->gameDraw(graphics);
				}
			}
		}

		if(state != GameState::START && state != GameState::CONTROLS && state != GameState::SETTINGS) {
			player->gameDraw(graphics);
		}

	switch(state) {
	case START:
	{

		if(this->titleGameText == nullptr) {
			titleGameText = new GraphicsText(graphics.getRenderer(), 60, "res/AGENCYB.TTF", "SWING MAN!", {255,0,0});

		}
		if(this->startGameText == nullptr) {
			startGameText = new GraphicsText(graphics.getRenderer(), 35, "res/AGENCYB.TTF", "Start Game", {255, 255, 255, 255});
		}

		if(this->controlsGameText == nullptr) {
			controlsGameText = new GraphicsText(graphics.getRenderer(), 35, "res/AGENCYB.TTF", "Controls", {255, 255, 255, 255});
		}

		if(this->startSettingsText == nullptr) {
			startSettingsText = new GraphicsText(graphics.getRenderer(), 35, "res/AGENCYB.TTF", "Settings", {255, 255, 255, 255});
		}

		SDL_Rect dot;


		dot.w = 15;
		dot.h = 15;
		dot.x = 285;
		dot.y = menu_dot_position_y[menu_position_index];

		SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 255, 255);

		graphics.drawFilledRect(dot);

		SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 0);

		titleGameText->draw(270, 120);


		startGameText->draw(320, 220);
		controlsGameText->draw(335, 280);
		startSettingsText->draw(335, 340);
		break;
	}
	case SETTINGS:
	{
		if(this->musicSettingsText == nullptr) {
			SDL_Color color = {255,255,255};
			musicSettingsText = new GraphicsText(graphics.getRenderer(), 40, "res/AGENCYB.TTF", (this->muteMusic ? "Unmute Music" : "Mute Music"), color);
		}

		if(this->soundSettingsText == nullptr) {
			SDL_Color color = {255,255,255};
			soundSettingsText = new GraphicsText(graphics.getRenderer(), 40, "res/AGENCYB.TTF", (this->muteSound ? "Unmute Sound" : "Mute Sound"), color);
		}
		if(this->difficultySettingsText == nullptr) {
			SDL_Color color = {255,255,255};
			difficultySettingsText = new GraphicsText(graphics.getRenderer(), 40, "res/AGENCYB.TTF", (this->difficulty ? "Difficulty: Easy" : "Difficulty: Hard"), color);
		}


		if(this->startScreenSettingsText == nullptr) {
			SDL_Color color = {255,255,255};
			startScreenSettingsText = new GraphicsText(graphics.getRenderer(), 40, "res/AGENCYB.TTF", "Start Screen", color);
		}

		SDL_Rect dot;


		dot.w = 15;
		dot.h = 15;
		dot.x = 285;
		dot.y = settings_menu_dot_position_y[settings_position_index];

		SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 255, 255);

		graphics.drawFilledRect(dot);

		SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 0);


		musicSettingsText->draw(320, 130);
		soundSettingsText->draw(320, 200);
		difficultySettingsText->draw(320, 270);
		startScreenSettingsText->draw(320, 340);
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

		endScoreGameText->draw(283, 240);
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
		score = new GraphicsText(graphics.getRenderer(), 30, "res/Arial.ttf", to_string(gamescore), {255, 255, 255, 255});


		if(this->pauseContinueText == nullptr) {
			SDL_Color color = {255,255,255};
			pauseContinueText = new GraphicsText(graphics.getRenderer(), 40, "res/AGENCYB.TTF", "Continue", color);
		}

		if(this->pauseNewGameText == nullptr) {
			SDL_Color color = {255,255,255};
			pauseNewGameText = new GraphicsText(graphics.getRenderer(), 40, "res/AGENCYB.TTF", "Start Screen", color);
		}

		SDL_Rect dot;


		dot.w = 15;
		dot.h = 15;
		dot.x = 285;
		dot.y = pause_menu_dot_position_y[pause_position_index];

		SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 255, 255);

		graphics.drawFilledRect(dot);

		SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 0);


		score->draw(10, GAME_HEIGHT/2);
		pauseNewGameText->draw(320, 250);
		pauseContinueText->draw(320, 180);
		break;
	}
	}



	graphics.flip();

}
