#pragma once
#include "Object.h"
#include "config.h"
#include "graphics.h"

class Fruit : public Object, public Collidable
{
	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT / 2;
	float size, speed, direction, image;
	class graphics::Brush brush;
	bool active = true;

public:
	Fruit(const class Game& game);
	~Fruit();
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Disk getCollisionHull() const override;
};