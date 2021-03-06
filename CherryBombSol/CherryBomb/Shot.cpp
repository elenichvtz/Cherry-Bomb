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
	if (game.getWeaponChoice() == 0)
	{
		brush.texture = std::string(PLAYER_ASSETS_PATH) + "gray_shot.png";
	}
	else
	{
		brush.texture = std::string(PLAYER_ASSETS_PATH) + "brown_shot.png";
	}
	brush.outline_opacity = 0.0f;
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
	speed = 0.5f;
	size = 35.0f;
}

Disk Shot::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size;
	return disk;
}
