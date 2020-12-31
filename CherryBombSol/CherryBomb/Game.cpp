#include "graphics.h"
#include "Game.h"
#include "config.h"
#include <iostream>

void Game::spawnCherry()
{
	/*if (!cherry)
		cherry = new Cherry(*this);*/

	currentSpawnTime += graphics::getDeltaTime();
	if (currentSpawnTime >= cherrySpawnInterval)
	{
		Cherry* cherry = new Cherry(*this);
		cherries.push_back(cherry);
		currentSpawnTime = 0;
	}
}

void Game::spawnFruit()
{
}

//void Game::checkCherry()
//{
//	if (cherry && !cherry->isActive())
//	{
//		delete cherry;
//		cherry = nullptr;
//	}
//}

void Game::checkShot()
{
	for (auto i : shots)
	{
		if (!i->isActive())
		{
			delete i;
			i = nullptr;
		}
	}
}

void Game::spawnShot()
{
	Shot* shot = new Shot(*this);

	shot->setX(player->getX());
	shot->setY(player->getY());
	shots.push_back(shot);
	std::cout << "shots size: " << shots.size() << std::endl;
}

/*bool Game::checkCollision()
{
	for (auto i : cherries)
	{
		if (player->checkCollision(i))
		{
			player->loseLife();
			player->incrementScore(); //just for debugging purposes, the score won't increment when u hit a cherry
		}
		else
			return false;
	}
}*/

bool Game::checkCollision()
{
	if (shots.empty() || cherries.empty())
	{
		//std::cout << "first loop" << std::endl;
		return false;
	}

	for (auto s : shots)
	{
		for (auto c : cherries)
		{

			Disk d1 = s->getCollisionHull();
			Disk d2 = c->getCollisionHull();

			float dx = d1.cx - d2.cx;
			float dy = d1.cy - d2.cy;

			if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
			{
				return true;
			}
			else
				return false;
		}
	}
}

void Game::resetPlayer() {
	if (player) {
		updateScoreboard(); //TO DO:: otan paizeis prwth fora den krataei to score gia kapoio logo,
		//to psaxnw akoma
		player->setScore(0);
		player->setLife(5);
		shots.clear();
		cherries.clear();
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

	/*if (cherry) 
	{
		delete cherry;
		cherry = nullptr;
	}*/
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
	graphics::drawText(100, 150, 30, "PRESS ENTER TO CHOOSE", br);

	///draw fork
	graphics::Brush brf;
	brf.texture = std::string(PLAYER_ASSETS_PATH) + "fork.png";
	brf.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 3, 300, 140, 140, brf);

	///draw chopsticks
	graphics::Brush brc;
	brc.texture = std::string(PLAYER_ASSETS_PATH) + "chopsticks.png";
	brc.fill_opacity = 1.0f;
	brc.outline_opacity = 0.0f;
	graphics::drawRect(2 * CANVAS_WIDTH / 3, 300, 200, 200, brc);


	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		//choose chopsticks
		weapon_choice = CHOPSTICKS;
	}

	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		//choose fork
		weapon_choice = FORK;
	}

	//draw outline for fork
	if (weapon_choice == FORK)
	{
		brf.fill_opacity = 0.0f;
		brf.outline_opacity = 1.0f;
		brf.outline_width = 2.0f;
		graphics::drawRect(CANVAS_WIDTH / 3, 300, 150, 150, brf);
	}
	else //draw outline for chopsticks
	{
		brc.fill_opacity = 0.0f;
		brc.outline_opacity = 1.0f;
		brc.outline_width = 2.0f;
		graphics::drawRect(2 * CANVAS_WIDTH / 3, 300, 150, 150, brc);
	}
}

void Game::drawGameScreen()
{
	//draw player
	if (player)
		player->draw();

	for(auto i :cherries)
		i->draw();

	for (auto s : shots)
		s->draw();

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
	}

	//checkCherry();
	spawnCherry();

	//old
	/*for (auto i : cherries)
	{
		i->update();
		if (checkCollision())
		{
			//bang!
			//graphics::playSound(std::string(AUDIO_ASSETS_PATH) + " ", 0.4f , false);

			delete i;
			i = nullptr;

			if (player->getLife() <= 0) game_status = END;
		}
	}*/

	//new
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed)
	{
		spawnShot();
	}


	if (!cherries.empty())
	{
		for (auto c : cherries) {
			c->update();
		}
	}
	//std::cout << "before s-> update" << std::endl;
	if (!shots.empty())
	{
		for (auto s : shots) {
			s->update();
		}
	}
	std::cout << "after s-> update" << std::endl;
	//for (auto c : cherries) {
	for (size_t c = 0; c < cherries.size(); c++) {
		//for (auto s : shots) {
		std::cout << "1st loop" << std::endl;
		for (size_t s = 0; s < shots.size(); s++) {
			std::cout << "2nd loop" << std::endl;
			if (checkCollision())
			{
				std::cout << "collision!!" << std::endl;
				cherries.erase(cherries.begin() + c);
				shots.erase(shots.begin() + s);
				//delete c;
				//c = nullptr;
				//delete s;
				//s = nullptr;
				player->loseLife();
				player->incrementScore(); //just for debugging purposes, the score won't increment when u hit a cherry
				std::cout << "lost a life!" << std::endl;
				if (player->getLife() <= 0) game_status = END;
			}
			break;
		}
	}
}

void Game::updateEndScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		resetPlayer();
		game_status = GAME;
	}
}
