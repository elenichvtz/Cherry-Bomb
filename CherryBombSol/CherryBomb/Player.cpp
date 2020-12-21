#include "Player.h"
#include "Game.h"
#include "Shot.h"
#include "graphics.h"

Player::Player(const Game& game)
	:Object(game)
{
}

void Player::update()
{
	//shoot
	if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP) ||
		graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		//checkShot();
		spawnShot();
	}

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

	//limitations
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;

	if (shot)
		shot->update();
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
	}

	if (shot)
		shot->draw();
}

void Player::init()
{
}

void Player::checkShot()
{
	if (shot && !shot->isActive())
	{
		delete shot;
		shot = nullptr;
	}
}

void Player::spawnShot()
{
	shot = new Shot(game);
	shot->setX(pos_x);
	shot->setY(pos_y);
}

bool Player::checkCollision(Cherry* cherry)
{
	if (!shot)
	{
		return false;
	}

	Disk d1 = shot->getCollisionHull();
	Disk d2 = cherry->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
	{
		return true;
	}
	else
		return false;
}
