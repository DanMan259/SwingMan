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

	Rope(Player* attached);

	void initiliaze(int x, int y);

	void update();

	void draw(Graphics& graphics);


private:
	Player* attached;
	vector<RopeNode> segments;
};
