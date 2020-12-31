#include "Player.h"
//#include "Game.h"
//#include "Shot.h"
#include "graphics.h"
#include <iostream>

Player::Player(const Game& game)
	:Object(game)
{
}

void Player::update()
{
	//shoot
	//if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP) ||
	//	graphics::getKeyState(graphics::SCANCODE_SPACE))
	//{
	//	checkShot();
	//	spawnShot();
	//}
	
	/*graphics::getMouseState(mouse);
	if (mouse.button_left_pressed)
	{
		spawnShot();
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

	//limitations
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;

	/*for (auto i : shots)
	{
		if (i && i->isActive())
			i->update();
	}*/
}

void Player::draw()
{
	graphics::Brush brush;
	if (game.getWeaponChoice() == 0)
	{
		brush.texture = std::string(PLAYER_ASSETS_PATH) + "fork.png";
	}
	else
	{
		brush.texture = std::string(PLAYER_ASSETS_PATH) + "chopsticks.png";
	}
	brush.outline_opacity = 0.0f;
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

	/*if (shots.size() > 0)
	{
		for (auto i : shots)
		{
			if (i && i->isActive())
				i->draw();
		}
	}*/
}

void Player::init()
{
	//shots.clear();
}

/*void Player::checkShot()
{
	for (auto i : Player::shots)
	{
		if (!i->isActive())
		{
			delete i;
			i = nullptr;
		}
	}
}

void Player::spawnShot()
{
	Shot* shot = new Shot(game);
	
	shot->setX(pos_x);
	shot->setY(pos_y);
	shots.push_back(shot);
	std::cout << "shots size: %f" << shots.size() << std::endl;
}

bool Player::checkCollision(Cherry* cherry)
{
	//TODO loop gia ola ta shots
	if (shots.size() > 0)
	{
		for (auto i : shots)
		{
			if (!i)
			{
				std::cout << "collision false" << std::endl;
				return false;
			}

			if (i->checkCollision(cherry))
			{
				std::cout << "collision true" << std::endl;
				delete i;
				i = nullptr;
				return true;
			}
			else
			{
				//bainei sunexeia edo -> to collision den einai pote true
				std::cout << "collision false2" << std::endl;
				return false;
			}
		}
	}
}*/
