#pragma once
#include "Object.h"
#include "Game.h"
#include "graphics.h"
#include "config.h"

class Player : public Object
{
	float speed = 8.0f;
	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT - 50;
	int score = 0;
	int life = 5;

    graphics::Brush brush;

public:
    Player(const class Game& game);
    void update() override;
    void draw() override;
    void init() override;

    float getX() { return pos_x; }

    float getY() { return pos_y; }

    int getScore() { return score; }
    void setScore(int i) { score = i; }
    void incrementScore(int s) { score += s; }

    int getLife() const { return life; }
    void setLife(int i) { life = i; }
    void loseLife() { life -= 1; }
};