#include "Shot.h"
#include "Game.h"
#include "graphics.h"

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
	graphics::Brush brush;
	brush.outline_opacity = 0.0f;
	brush.fill_color[1] = 1.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);

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
	speed = 0.4f;
	size = 30.0f;
}

Disk Shot::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size;
	return disk;
}

/*bool Shot::checkCollision(Cherry* cherry)
{
	Disk d1 = getCollisionHull();
	Disk d2 = cherry->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
	{
		return true;
	}
	else
		return false;
}*/
