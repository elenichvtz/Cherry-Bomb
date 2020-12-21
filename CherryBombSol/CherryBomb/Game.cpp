#include "graphics.h"
#include "Game.h"
#include "config.h"
#include <iostream>

void Game::spawnCherry()
{
	if (!cherry)
		cherry = new Cherry(*this);
}

void Game::spawnFruit()
{
}

void Game::checkCherry()
{
	if (cherry && !cherry->isActive())
	{
		delete cherry;
		cherry = nullptr;
	}
}

bool Game::checkCollision()
{
	//den ginetai pote true
	if (player->checkCollision(cherry))
	{
		std::cout << "yep";
		player->loseLife();
		player->incrementScore(); //just for debugging purposes, the score won't increment when u hit a cherry
	}
	else
		return false;
}

void Game::resetPlayer() {
	if (player) {
		updateScoreboard(); //TO DO:: otan paizeis prwth fora den krataei to score gia kapoio logo,
		//to psaxnw akoma
		player->setScore(0);
		player->setLife(5);
	}
}

void Game::updateScoreboard() {
	if (player) {
		scoreboard.push_back(player->getScore());
		scoreboard.sort();
		if (scoreboard.size() > 5) scoreboard.pop_back();
		//setScoreboard(scoreboard);
	}
}

void Game::update()
{
	if (game_status == TITLE) updateTitleScreen();
	else if (game_status == WEAPON) updateWeaponScreen();
	else if (game_status == GAME) updateGameScreen();
	else updateEndScreen();
}

void Game::draw()
{
	graphics::Brush brush;
	brush.outline_opacity = 0.0f;
	brush.fill_color[0] = 0.0f;
	brush.fill_color[1] = 0.0f;
	brush.fill_color[2] = 0.0f;
	graphics::setWindowBackground(brush);
	
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, brush);
	
	if (game_status == TITLE) drawTitleScreen();
	else if (game_status == WEAPON) drawWeaponScreen();
	else if (game_status == GAME) drawGameScreen();
	else drawEndScreen();
}

void Game::init()
{
	graphics::setFont(std::string(FONT_ASSETS_PATH) + "ARCADECLASSIC.ttf");
	graphics::playMusic(std::string(AUDIO_ASSETS_PATH) + "NCT_127-Cherry_Bomb_Instrumental.mp3", 0.4f, true, 3000);
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

	if (cherry) 
	{
		delete cherry;
		cherry = nullptr;
	}

	if(shot)
	{
		delete shot;
		shot = nullptr;
	}
}

void Game::drawTitleScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	graphics::drawText(200, 200, 100, "CHERRY BOMB", br);

	float flash = 0.5f + 0.9f * sinf(graphics::getGlobalTime() / 170);
	br.fill_color[0] += flash;
	br.fill_color[1] += flash;
	br.fill_color[2] += flash;
	graphics::drawText(250, 300, 50, "PRESS SPACE TO START", br);

}

void Game::drawWeaponScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	//char weapon[40];
	//sprintf_s(weapon, "CHOOSE YOUR WEAPON");
	graphics::drawText(100, 100, 60, "CHOOSE YOUR WEAPON", br);
	//TO DO: add weapons and choose player
	graphics::drawText(100, 150, 30, "PRESS ENTER TO CONTINUE", br);

}

void Game::drawGameScreen()
{
	//draw player
	if (player)
		player->draw();

	if (cherry)
		cherry->draw();

	//UI/info layer -> could become a separate class
	if (player)
	{
		//score
		char score[40];
		sprintf_s(score, "SCORE %i", player->getScore());
		graphics::Brush br;
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		graphics::drawText(50, 50, 40, score, br);
	}
	//life
	float life = player ? player->getLife() : 0;

	graphics::Brush br;
	br.texture = std::string(PLAYER_ASSETS_PATH) + "heart.png";
	br.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;
	br.outline_color[0] = 1.0f;
	br.outline_color[1] = 1.0f;
	br.outline_color[2] = 1.0f;
	int x = 180;
	for (int i = 0; i < life; i++)
	{
		graphics::drawRect(CANVAS_WIDTH - x, 30, 40, 40, br);
		x -= 30;
	}

}

void Game::drawEndScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	graphics::drawText(280, 100, 80, "GAME OVER", br);
	graphics::drawText(300, 150, 30, "PRESS ENTER TO PLAY AGAIN", br);
	graphics::drawText(350, 250, 30, "SCOREBOARD", br);

	int y = 300;
	for (auto const& i : scoreboard) {
		graphics::drawText(400, y, 30, std::to_string(i*y), br); 
		//ebala to *y gia na dw an kanei kala to sort, meta to vgazoume
		//den ginetai kala to sort...
		y += 30;
	}
}

void Game::updateTitleScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		game_status = WEAPON;
	}
}

void Game::updateWeaponScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		game_status = GAME;
	}
}

void Game::updateGameScreen()
{
	if (!player_initialized && graphics::getGlobalTime() > 1000)
	{
		player = new Player(*this);
		player_initialized = true;
	}

	if (player)
	{
		player->update();
		if (checkCollision())
		{
			//bang!
			//graphics::playSound(std::string(AUDIO_ASSETS_PATH) + " ", 0.4f , false);

			delete cherry;
			cherry = nullptr;

			if (player->getLife() <= 0) game_status = END;
		}
	}

	checkCherry();
	spawnCherry();

	if (cherry)
		cherry->update();
}

void Game::updateEndScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		resetPlayer();
		game_status = GAME;
	}
}
