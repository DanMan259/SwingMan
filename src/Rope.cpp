#include <SDL.h>

#include "Entity.h"
#include "Graphics.h"
#include "Rope.h"
#include <cmath>
#include <iostream>

namespace rope_constants {
	int NODES = 10;
}

// Constant for PI
const double PI = 3.14159265;


Rope::Rope(Player *attached, Entity* swingingBlock) {
	// Initializes the rope class with the required variables
	this->attached = attached; // Player that is attached
	this->swingingBlock = swingingBlock; // Block that the player is attached to
	this->attached->getGameWin()->getSoundMixer().playSound(attached->getGameWin(), "rope"); // Play the sound for the rope
	this->vectorX = swingingBlock->getX()-attached->getX(); // Initializing the y vector of the rope
	this->vectorY = -swingingBlock->getY()+attached->getY(); // Initializing the x vector of the rope
	this->time = 0; // time init
	this->length = sqrt((vectorX*vectorX)+(vectorY*vectorY)); // getting the length of the rope
	this->initAngle = acos(abs(vectorY)/length); // calculating the initial angle
	this->ropeStart = SDL_GetTicks(); // Getting the start time of the rope
	this->angularFreq = -0.1*(350/length); // Calculating the angular velocity based upon the vectors

}

void Rope::update() {
	time = (SDL_GetTicks() - ropeStart)*(PI/180); // calculate current time since init
	attached->setYVelocity(int(length*angularFreq*-sin(angularFreq*time+initAngle))); // Calc the Y velocity based upon time
	attached->setY(int(length*cos(angularFreq*time+initAngle))+swingingBlock->getY()); // Render Y displacement based upon time
	attached->setXVelocity(int(length*angularFreq*-cos(angularFreq*time+initAngle)/2.8)); // Calc the Y velocity based upon time for scrolling mechanic


}
// accessor for the attached block
Entity* Rope::getSwingingBlock() const {
	return swingingBlock;
}

// Code to render a line in sdl between the player and the block
void Rope::draw(Graphics& graphics) {
	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 255, 255);
	graphics.drawLine(attached->getX() + attached->getWidth()/2, attached->getY() + attached->getHeight()/2, swingingBlock->getX()+swingingBlock->getWidth()/2, swingingBlock->getY() + swingingBlock->getHeight());
	SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 0);
}
