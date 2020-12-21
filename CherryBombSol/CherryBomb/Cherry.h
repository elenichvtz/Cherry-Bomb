#pragma once
#include "Object.h"
#include "config.h"

class Cherry :public Object
{
	//thelei kai kateuthinsi
	float pos_x, pos_y, size, speed, rotation;
	class graphics::Brush brush;
	bool active = true;

public:
	void update()override;

	void draw() override;

	void init() override;

	bool getCherryState() { return active; }

	Cherry(const class Game& game);

	~Cherry();

	float getx() { return pos_x; }
	float gety() { return pos_y; }
};