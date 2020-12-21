#pragma once
#include "graphics.h"
#include "Object.h"
#include "config.h"

class Player : public Object, public Collidable //it's not actually collidable so we will remove it later
{
	float speed = 8.0f;
	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT - 50;
	int score = 0;
	int life = 5;

public:
    Player(const class Game& mygame);
    void update() override;
    void draw() override;
    void init() override;
    int getScore() { return score; }
    Disk getCollisionHull() const override; //for testing purposes
    int getLife() const { return life; }
    void loseLife() { life -= 1; }
};