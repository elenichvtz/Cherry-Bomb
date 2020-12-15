#pragma once
#include "graphics.h"
#include "Object.h"
#include "config.h"

class Player : public Object
{
	float pos_x = CANVAS_WIDTH / 2, pos_y = 9 * CANVAS_HEIGHT / 10, speed = 80.f;
	int life = 3;
	int score = 0;

public:
	void update() override;

	void draw() override;

	void init() override;

	float getPlayerX() { return pos_x; };

	float getPlayerY() { return pos_y; };

	int getPlayerLives() { return life; };

	int getPlayerScore() { return score; };

	void updatePlayerScore(int s) { score += s; };
};