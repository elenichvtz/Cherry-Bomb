#include "Fruit.h"
#include "functions.h"
#include "Game.h"

Fruit::Fruit(const Game& game)
	:Object(game)
{
	init();
}

Fruit::~Fruit()
{
}

void Fruit::update()
{
	//rotation += 0.15f * graphics::getDeltaTime();
	//rotation = fmodf(rotation, 360);
	if (direction == 0.0f)
		pos_x += speed * graphics::getDeltaTime();
	else
		pos_x -= speed * graphics::getDeltaTime();

	if (pos_x < -size || pos_x > CANVAS_WIDTH + size) active = false;
}

void Fruit::draw()
{
	//graphics::setOrientation(rotation);

	if(image == 0.0f)
	{
		brush.texture = std::string(FRUIT_ASSETS_PATH) + "apple.png";
	}
	else if (image == 1.0f)
	{
		brush.texture = std::string(FRUIT_ASSETS_PATH) + "lemon.png";
	}
	else if (image == 2.0f)
	{
		brush.texture = std::string(FRUIT_ASSETS_PATH) + "orange.png";
	}
	else if (image == 3.0f)
	{
		brush.texture = std::string(FRUIT_ASSETS_PATH) + "cherry.png";
	}

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

void Fruit::init()
{
	//random fruit with rand0to3()
	image = rand0to3();
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

Disk Fruit::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size / 3.3;
	return disk;
}

float Fruit::fruitScore()
{
	if (size < 110.0f)
		return 50;
	else
		return 25;
}
