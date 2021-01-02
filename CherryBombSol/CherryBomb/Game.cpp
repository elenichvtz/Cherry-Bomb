#include "Game.h"
#include "config.h"
#include <iostream>

//void Game::spawnCherry()
//{
//	cherrycurrentSpawnTime += graphics::getDeltaTime();
//	if (cherrycurrentSpawnTime >= cherrySpawnInterval)
//	{
//		Cherry* cherry = new Cherry(*this);
//		cherries.push_back(cherry);
//		cherrycurrentSpawnTime = 0;
//	}
//}

void Game::spawnFruit()
{
	fruitcurrentSpawnTime += graphics::getDeltaTime();
	if (fruitcurrentSpawnTime >= fruitSpawnInterval)
	{
		Fruit* fruit = new Fruit(*this);
		if (fruit->getImage() == 3.0f)
		{
			cherries.push_back(fruit);
		}
		else
		{
			fruits.push_back(fruit);
		}
		fruitcurrentSpawnTime = 0;
	}
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

bool Game::checkCollision(Shot* shot, Fruit* fruit)
{
	//if fruit is cherry
	if (fruit->getImage() == 0.03f)
	{
		if (shots.empty() || cherries.empty())
		{
			return false;
		}
		Disk d1 = shot->getCollisionHull();
		Disk d2 = fruit->getCollisionHull();

		float dx = d1.cx - d2.cx;
		float dy = d1.cy - d2.cy;

		if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		if (shots.empty() || fruits.empty())
		{
			return false;
		}
		Disk d1 = shot->getCollisionHull();
		Disk d2 = fruit->getCollisionHull();

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

void Game::checkTotalCherryCollision()
{
	for (size_t s = 0; s < shots.size(); s++) 
	{
		for (size_t c = 0; c < cherries.size(); c++) 
		{
			if (checkCollision(shots[s], cherries[c]))
			{
				std::cout << "cherry collision!!" << std::endl;

				//bang!
				//graphics::playSound(std::string(AUDIO_ASSETS_PATH) + " ", 0.4f , false);

				cherries.erase(cherries.begin() + c);
				shots.erase(shots.begin() + s);
				player->loseLife();
				
				std::cout << "lost a life!" << std::endl;
				if (player->getLife() <= 0) game_status = END;
				break;
			}
		}
	}
}

void Game::checkTotalFruitCollision()
{
	for (size_t s = 0; s < shots.size(); s++) 
	{
		for (size_t f = 0; f < fruits.size(); f++)
		{
			if (checkCollision(shots[s], fruits[f]))
			{
				std::cout << "fruit collision!!" << std::endl;

				//bang!
				//graphics::playSound(std::string(AUDIO_ASSETS_PATH) + " ", 0.4f , false);

				fruits.erase(fruits.begin() + f);
				shots.erase(shots.begin() + s);
				
				player->incrementScore(fruits[f]->fruitScore());
				break;
			}
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

	/*if (cherries) 
	{
		delete cherries;
		cherries = nullptr;
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
	graphics::drawText(250, 300, 50, "CLICK HERE TO PLAY", br);
}

void Game::drawWeaponScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	graphics::drawText(100, 100, 60, "CHOOSE YOUR WEAPON", br);
	//TO DO: add weapons and choose player
	//graphics::drawText(100, 150, 30, "PRESS ENTER TO CHOOSE", br);

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

	//if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT))
	graphics::getMouseState(mouse);
	if (mouse.cur_pos_x >= CANVAS_WIDTH/3 - 70 && mouse.cur_pos_x <= CANVAS_WIDTH / 3 + 70 && 
		mouse.cur_pos_y >= 300 - 70 && mouse.cur_pos_y <= 300 + 70)
	{
		//choose fork
		weapon_choice = FORK;
	}

	//if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT))
	graphics::getMouseState(mouse);
	if (mouse.cur_pos_x >= 2 * CANVAS_WIDTH / 3 - 100 && mouse.cur_pos_x <= 2*CANVAS_WIDTH/3 + 100 &&
		mouse.cur_pos_y >= 300 - 100 && mouse.cur_pos_y <= 300 + 100)
	{
		//choose chopsticks
		weapon_choice = CHOPSTICKS;
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

	for (auto f : fruits)
		f->draw();

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
	graphics::drawText(300, 150, 30, "CLICK ANYWHERE TO PLAY AGAIN", br);
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
	graphics::getMouseState(mouse);
	if (mouse.cur_pos_x >= 250 && mouse.cur_pos_x <= 700 &&
		mouse.cur_pos_y >= 300 - 50 && mouse.cur_pos_y <=300 && mouse.button_left_pressed)
	{
		game_status = WEAPON;
	}
}

void Game::updateWeaponScreen()
{
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed)
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

	spawnFruit();

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

	if (!shots.empty())
	{
		for (auto s : shots) {
			s->update();
		}
	}

	if (!fruits.empty())
	{
		for (auto f : fruits) {
			f->update();
		}
	}

	checkTotalCherryCollision();

	checkTotalFruitCollision();
}

void Game::updateEndScreen()
{
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed)
	{
		resetPlayer();
		game_status = GAME;
	}
}
