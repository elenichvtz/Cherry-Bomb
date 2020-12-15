#pragma once
#include "graphics.h"
#include "Object.h"
#include "config.h"

class Cherry :public Object
{
	float pos_x = CANVAS_WIDTH / 2, pos_y = 9 * CANVAS_HEIGHT / 10, speed = 80.f;
public:
	void update()override;

	void draw() override;

	void init() override;

	Cherry();

	~Cherry();
};