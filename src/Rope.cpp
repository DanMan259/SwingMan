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
	this->angle = 0;
	this->vectorX = 0;
	this->vectorY = 0;
	this->time = 0;
	this->length = 0;
	this->ropeStart = SDL_GetTicks();
}

void Rope::update() {
	vectorX = swingingBlock->getX()-attached->getX();
	vectorY = swingingBlock->getY()-attached->getY();
	length = sqrt((vectorX*vectorX)+(vectorY*vectorY));
	angle = acos(vectorY/length);
	if(isnan(angle)){
		cout<<"VectorY  = "<<vectorY<<"ropelen = "<< length << endl;
	}else{
		cout<<"Correct VectorY  = "<<vectorY<<" ropelen = "<< length << endl;
	}
	time = (SDL_GetTicks() - ropeStart)*(PI/180) / 40;
	attached->setX(int(length*sin(time+angle))+(swingingBlock->getX() - attached->getWidth()));
	attached->setY(int(length*cos(time+angle))+swingingBlock->getY());

}

Entity* Rope::getSwingingBlock() const {
	return swingingBlock;
}

void Rope::draw(Graphics& graphics) {
	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 255, 255);
	graphics.drawLine(attached->getX() + attached->getWidth(), attached->getY(), swingingBlock->getX(), swingingBlock->getY() + swingingBlock->getHeight());
	SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 0);
}

//
//void Rope::initiliaze(int x, int y) {
//
//	for(int i = 0; i < rope_constants::NODES; i++) {
//		RopeNode node;
//		node.positionX = x + i * 2;
//		node.positionY = y;
//		node.oldPositionX = node.positionX;
//		node.oldPositionY = node.positionY;
//		node.velocityX = 0;
//		node.velocityY = 0;
//		node.mass = i;
//
//		this->segments.push_back(node);
//	}
//}
//
//void Rope::draw(Graphics& graphics) {
//	for(size_t i = 0; i < segments.size()-1; i++) {
//		RopeNode nodeOne = segments.at(i);
//		RopeNode nodeTwo = segments.at(i+1);
//
//		int x1 = nodeOne.positionX;
//		int y1 = nodeOne.positionY;
//		int x2 = nodeTwo.positionX;
//		int y2 = nodeTwo.positionY;
//
//		cout << "ma" << x1 << endl;
//		SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 255, 255);
//
//		graphics.drawLine(x1, y1, x2, y2);
//		SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 0);
//
//	}
