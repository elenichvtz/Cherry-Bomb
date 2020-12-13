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
}

void Game::init()
{
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
