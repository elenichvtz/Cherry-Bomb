#include "Player.h"
//#include "config.h"
#include "Game.h"
#include "graphics.h"

Player::Player(const Game& game)
	:Object(game)
{
}

void Player::update()
{
	//shoot
	/*if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP) ||
		graphics::getKeyState(graphics::SCANCODE_SPACE))
	{

	}*/

	//A or LEFT ARROW to move left
	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		pos_x -= speed * graphics::getDeltaTime() / 10.0f;
	}
	//D or RIGHT ARROW to move right
	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}

	///////////////////////////////// collision check
	//move up
	if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP))
	{
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;
	}

	//move down
	if (graphics::getKeyState(graphics::SCANCODE_S) || graphics::getKeyState(graphics::SCANCODE_DOWN))
	{
		pos_y += speed * graphics::getDeltaTime() / 10.0f;
	}
	/////////////////////////////////

	//limitations
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
}

void Player::draw()
{
	graphics::Brush brush;
	brush.texture = std::string(PLAYER_ASSETS_PATH) + "fork.png";
	brush.outline_opacity = 0.0f;

	//draw fork
	graphics::drawRect(pos_x, pos_y, 100, 100, brush);
	if (game.getDebugMode()) //will delete later
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

void Player::init()
{
}

//will delete later bc the player won't have to collide
Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 50.0f;
	return disk;
}
