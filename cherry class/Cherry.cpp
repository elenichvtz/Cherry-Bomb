#include "Cherry.h"
#include "functions.h"
#include "Game.h"

void Cherry::update()
{
	//rotation += 0.15f * graphics::getDeltaTime();
	//rotation = fmodf(rotation, 360);
	if(direction==0.0f)
		pos_x += speed * graphics::getDeltaTime();
	else
		pos_x -= speed * graphics::getDeltaTime();

	if (pos_x < -size || pos_x > CANVAS_WIDTH + size) active = false;
}

void Cherry::draw()
{
	//graphics::setOrientation(rotation);
	brush.texture = std::string(FRUIT_ASSETS_PATH) + "cherry.png";
	brush.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	
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
	//if 0 go left, else right
	if (rand0or1() == 0.0f)
	{
		direction = 0.0f;
		pos_x = -110;
	}
	else
	{
		direction = 1.0f;
		pos_x = CANVAS_WIDTH + 110;
	}
	pos_y = 100 + 200 * rand0to1();
	size = 60 + 100 * rand0to1();
	
	//rotation = 360 * rand0to1();
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