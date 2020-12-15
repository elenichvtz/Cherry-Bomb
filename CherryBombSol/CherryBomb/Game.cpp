#include "graphics.h"
#include "Game.h"
#include "config.h"

void Game::update()
{
	if (!player_init)
	{
		player = new Player();
		player_init = true;
	}

	if (player)
		player->update();
}

void Game::draw()
{
	//TODO: draw background -> alla boroume apla na to afisoume ena xroma (autos vazei eikona)

	//draw player
	if (player)
		player->draw();

	//UI
	if (player)
	{
		char lives[10];
		//dynamically shows lives
		sprintf_s(lives, "Lives %x", player->getPlayerLives());

		char score[10];
		//dynamically shows score
		sprintf_s(score, "Score %x", player->getPlayerScore());
		//player->updatePlayerScore(2);
		graphics::Brush brush;
		brush.fill_color[0] = 0.0f;
		brush.fill_color[1] = 0.0f;
		brush.fill_color[2] = 0.0f;

		graphics::drawText(CANVAS_WIDTH / 12, CANVAS_HEIGHT / 10, 50, score, brush);
		graphics::drawText(CANVAS_WIDTH / 12, CANVAS_HEIGHT / 7, 30, lives, brush);
		graphics::drawText(CANVAS_WIDTH / 12, CANVAS_HEIGHT / 5, 20, "Press A for left and D for right", brush);
	}
}

void Game::init()
{
	graphics::setFont(std::string(FONT_ASSETS_PATH) + "ARCADECLASSIC.ttf");
	graphics::playMusic(std::string(MUSIC_ASSETS_PATH) + "NCT_127-Cherry_Bomb_Instrumental.mp3", 0.4f, true, 3000);
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
	{
		delete player;
		player = nullptr;
	}
}
