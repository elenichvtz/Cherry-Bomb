#pragma once
#include "Object.h"
#include "config.h"
#include "graphics.h"

class Cherry : public Object, public Collidable
{

	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT / 2;
	float size, speed, direction;
	class graphics::Brush brush;
	bool active = true;

public:
	Cherry(const class Game& game);
	~Cherry();
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Disk getCollisionHull() const override;

	//float getx() { return pos_x; }
	//float gety() { return pos_y; }
};