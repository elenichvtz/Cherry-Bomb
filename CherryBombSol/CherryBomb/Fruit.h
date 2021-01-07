#pragma once
#include "Object.h"
#include "config.h"
#include "graphics.h"

class Fruit : public Object, public Collidable
{
	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT / 2;
	float size, speed, direction, image;
	bool active = true;

	graphics::Brush brush;
public:
	Fruit(const class Game& game);
	~Fruit();
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Disk getCollisionHull() const override;

	float getImage() { return image; }

	int fruitScore();

	void setFruitSpeed(float x) { speed = x; }

	float getX() const { return pos_x; }
	float getY() const { return pos_y; }
	float getSize() const { return size; }
};