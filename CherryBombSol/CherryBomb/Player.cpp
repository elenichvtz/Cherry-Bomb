#include "Player.h"

Player::Player(const Game& game)
	:Object(game)
{
}

void Player::update()
{
	//A or LEFT ARROW to move left
	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		pos_x -= speed * graphics::getDeltaTime() / 20.0f;
	}
	//D or RIGHT ARROW to move right
	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		pos_x += speed * graphics::getDeltaTime() / 20.0f;
	}

	//limitations
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
}

void Player::draw()
{
	if (game.getWeaponChoice() == 0)
	{
		brush.texture = std::string(PLAYER_ASSETS_PATH) + "fork.png";
	}
	else
	{
		brush.texture = std::string(PLAYER_ASSETS_PATH) + "chopstick.png";
	}
	brush.outline_opacity = 0.0f;

	//draw fork
	graphics::drawRect(pos_x, pos_y, 100, 100, brush);
	if (game.getDebugMode())
	{
		brush.outline_opacity = 0.5f;
		brush.texture = "";
		brush.fill_color[0] = 0.3f;
		brush.fill_color[1] = 0.6f;
		brush.fill_color[2] = 0.4f;
		brush.fill_opacity = 0.5f;
	}
}

void Player::init()
{
}
