#include "Shot.h"
#include "Game.h"

Shot::Shot(const Game& game)
	:Object(game)
{
	init();
}

void Shot::update()
{
	pos_y -= speed * graphics::getDeltaTime();
	if (pos_y < size) active = false;
}

void Shot::draw()
{
	brush.outline_opacity = 0.0f;
	brush.fill_color[1] = 1.0f;
	
	graphics::drawDisk(pos_x, pos_y, size, brush);

	if (game.getDebugMode())
	{
		brush.outline_opacity = 0.5f;
		brush.texture = "";
		brush.fill_color[0] = 0.3f;
		brush.fill_color[1] = 0.6f;
		brush.fill_color[2] = 0.4f;
		brush.fill_opacity = 0.5f;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, brush);
	}
}

void Shot::init()
{
	speed = 0.45f;
	size = 20.0f;
}

Disk Shot::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size;
	return disk;
}
