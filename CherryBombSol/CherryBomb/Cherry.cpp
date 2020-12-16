#include "graphics.h"
#include "Cherry.h"
#include "config.h"
#include <random>
#include "functions.h"
#include "Game.h"
#include <iostream>

void Cherry::update()
{
	pos_x -= speed * graphics::getDeltaTime();
	rotation += 1.0f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);
	if (pos_x < -size)
		active = false;
}

void Cherry::draw()
{
	graphics::setOrientation(rotation);
	brush.texture = std::string(FRUIT_ASSETS_PATH) + "cherry.png";
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	//pairnei to texture alla den emfanizei tin eikona opoia ki an valeis
	std::cout << brush.texture;
	graphics::resetPose();
}

void Cherry::init()
{
	speed = 1.0f;
	pos_x = CANVAS_WIDTH + 1.1f * size;
	pos_y = CANVAS_HEIGHT * rand0to1();
	size = 50 + 100 * rand0to1();
	rotation = 360 * rand0to1();
	brush.outline_opacity = 0.0f;
}

Cherry::Cherry(const Game& game)
	:Object(game)
{
	init();
}

Cherry::~Cherry()
{
	
}
