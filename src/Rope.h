#pragma once

#include "Player.h"

struct RopeNode {
	int velocityX, velocityY;
	int positionX, positionY;
	int oldPositionX, oldPositionY;
	int mass;
};

class Player;
class Rope {
public:

	Rope(Player* attached, Entity *swingingBlock);

	void initiliaze(int x, int y);

	void update();

	void draw(Graphics& graphics);

	Entity* getSwingingBlock() const;


private:
	Player* attached;

	Entity* swingingBlock;

	vector<RopeNode> segments;
};
