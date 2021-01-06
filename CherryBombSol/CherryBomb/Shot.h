#pragma once
#include "Object.h"
#include "graphics.h"

class Shot : public Object, public Collidable
{
	float size, pos_x, pos_y, speed;
	bool active = true;
	graphics::Brush brush;

public:
	Shot(const class Game& game);

	void update() override;
	void draw() override;
	void init() override;

	void setX(float x) { pos_x = x; }
	void setY(float y) { pos_y = y; }

	Disk getCollisionHull() const override;

	bool isActive() { return active; }
};