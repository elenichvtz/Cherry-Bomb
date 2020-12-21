//#include "graphics.h"
#include "Cherry.h"
//#include "config.h"
#include "functions.h"
#include "Game.h"
//#include <iostream>

void Cherry::update()
{
	//rotation += 0.15f * graphics::getDeltaTime();
	//rotation = fmodf(rotation, 360);
	pos_x -= speed * graphics::getDeltaTime();
	//pos_x += speed * graphics::getDeltaTime(); an ekane spawn deksia

	if (pos_x < -size) active = false;
}

void Cherry::draw()
{
	//graphics::setOrientation(rotation);
	brush.texture = std::string(FRUIT_ASSETS_PATH) + "cherry.png";
	brush.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	//pairnei to texture alla den emfanizei tin eikona opoia ki an valeis
	//std::cout << brush.texture;
	//graphics::resetPose();
	if (game.getDebugMode())
	{
		graphics::Brush brush;
		brush.outline_opacity = 1.0f;
		brush.texture = "";
		brush.fill_color[0] = 1.0f;
		brush.fill_color[1] = 0.3f;
		brush.fill_color[2] = 0.3f;
		brush.fill_opacity = 0.5f;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, brush);
	}
}

void Cherry::init()
{
	speed = 0.3f;
	pos_x = CANVAS_WIDTH + 110;
	pos_y = 100 + 200 * rand0to1();
	size = 100;
	
	//size = 60 + 100 * rand0to1();
	//rotation = 360 * rand0to1();
	//brush.outline_opacity = 0.0f;
}

Cherry::Cherry(const class Game& game)
	:Object(game)
{
	init();
}

Cherry::~Cherry()
{
	
}

Disk Cherry::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size / 3.3;
	return disk;
}