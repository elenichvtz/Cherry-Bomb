#include "graphics.h"
#include "Player.h"
#include "config.h"
#include "Game.h"

Player::Player(const Game& game)
	:Object(game)
{
}

void Player::update()
{
	//A for left
	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		pos_x -= speed * graphics::getDeltaTime() / 150.f;
	}
	//D for right
	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		pos_x += speed * graphics::getDeltaTime() / 150.f;
	}

	//limitations
	if (pos_x < 0)
	{
		pos_x = 0;
	}
	if (pos_x > CANVAS_WIDTH)
	{
		pos_x = CANVAS_WIDTH;
	}
}

void Player::draw()
{
	graphics::Brush brush;
	brush.outline_opacity = 0.0f;

	brush.texture = std::string(PLAYER_ASSETS_PATH) + "player.png";
	brush.fill_opacity = 1.0f;
	//den evala rotation de nomizo oti xreiazetai
	graphics::drawRect(pos_x, pos_y, 250, 250, brush);
	brush.texture = "";
}

void Player::init()
{
}
