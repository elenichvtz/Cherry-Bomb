#pragma once
#include "Object.h"
#include "config.h"

class Cherry :public Object
{
	float pos_x, pos_y, size, speed, rotation;
	graphics::Brush brush;
	bool active = true;

public:
	void update()override;

	void draw() override;

	void init() override;

	bool getCherryState() { return active; }

	Cherry(const class Game& game);

	~Cherry();
};