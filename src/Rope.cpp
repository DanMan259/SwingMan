#include <SDL.h>

#include "Entity.h"
#include "Graphics.h"
#include "Rope.h"
#include <cmath>
#include <iostream>

namespace rope_constants {
	int NODES = 10;
}

const double PI = 3.14159265;


Rope::Rope(Player *attached, Entity* swingingBlock) {
	this->attached = attached;
	this->swingingBlock = swingingBlock;
	this->attached->getGameWin()->getSoundMixer().playSound(attached->getGameWin(), "rope");
	this->vectorX = swingingBlock->getX()-attached->getX();
	this->vectorY = -swingingBlock->getY()+attached->getY();
	this->time = 0;
	this->length = sqrt((vectorX*vectorX)+(vectorY*vectorY));
	this->initAngle = acos(abs(vectorY)/length);
	this->ropeStart = SDL_GetTicks();
	this->angularFreq = -0.1*(350/length);

}

void Rope::update() {
	time = (SDL_GetTicks() - ropeStart)*(PI/180);
	attached->setYVelocity(int(length*angularFreq*-sin(angularFreq*time+initAngle)));
	attached->setY(int(length*cos(angularFreq*time+initAngle))+swingingBlock->getY());
	attached->setXVelocity(int(length*angularFreq*-cos(angularFreq*time+initAngle)/2.8));//2.8 is just a constant that slows down the screen since it is too fast without it


}

Entity* Rope::getSwingingBlock() const {
	return swingingBlock;
}

void Rope::draw(Graphics& graphics) {
	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 255, 255);
	graphics.drawLine(attached->getX() + attached->getWidth()/2, attached->getY() + attached->getHeight()/2, swingingBlock->getX()+swingingBlock->getWidth()/2, swingingBlock->getY() + swingingBlock->getHeight());
	SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 0);
}
