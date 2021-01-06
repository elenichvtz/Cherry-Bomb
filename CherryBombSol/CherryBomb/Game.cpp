#include "Game.h"
#include "config.h"

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

void Game::checkFruits(size_t f)
{
	if ((fruits[f]->isActive()) == false)
	{
		fruits.erase(fruits.begin() + f);
	}
}

void Game::checkCherries(size_t c)
{
	if ((cherries[c]->isActive()) == false)
	{
		cherries.erase(cherries.begin() + c);
	}
}

void Game::checkShots()
{
	for (size_t s = 0; s < shots.size(); s++)
	{
		if ((shots[s]->isActive())==false)
		{
			shots.erase(shots.begin() + s);
		}
	}
}

void Game::spawnShot()
{
	Shot* shot = new Shot(*this);

	shot->setX(player->getX());
	shot->setY(player->getY());
	shots.push_back(shot);
}

void Game::increasefruitSpawn()
{
	if (player->getScore() > 500)
		setfruitSpawnInterval(200.0f);
	else if (player->getScore() > 1000)
		setfruitSpawnInterval(100.0f);
	else if (player->getScore() > 1500)
		setfruitSpawnInterval(50.0f);
}

bool Game::checkCollision(Shot* shot, Fruit* fruit)
{
	//if fruit is cherry
	if (fruit->getImage() == 3.0f)
	{
		if (shots.empty() || cherries.empty())
		{
			return false;
		}
	}
	else
	{
		if (shots.empty() || fruits.empty())
		{
			return false;
		}
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

void Game::checkTotalCherryCollision()
{
	for (size_t s = 0; s < shots.size(); s++) 
	{
		for (size_t c = 0; c < cherries.size(); c++) 
		{
			if (checkCollision(shots[s], cherries[c]))
			{
				//bang!
				graphics::playSound(std::string(AUDIO_ASSETS_PATH) + "explosion.wav", 0.5f , false);

				explosion = true;

				explosion_x = cherries[c]->getX();
				explosion_y = cherries[c]->getY();
				explosion_size = cherries[c]->getSize();

				cherries.erase(cherries.begin() + c);
				shots.erase(shots.begin() + s);

				player->loseLife();
				
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
				player->incrementScore(fruits[f]->fruitScore());

				fruits.erase(fruits.begin() + f);
				shots.erase(shots.begin() + s);
			
				break;
			}
		}
	}
}

void Game::resetPlayer() 
{
	if (player) {
		player->setScore(0);
		player->setLife(PLAYER_LIFE);
		shots.clear();
		cherries.clear();
	}
}

void Game::update()
{
	if (game_status == TITLE) updateTitleScreen();
	else if (game_status == INSTRUCTIONS) updateInstructionScreen();
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
	else if (game_status == INSTRUCTIONS) drawInstructionScreen();
	else if (game_status == WEAPON) drawWeaponScreen();
	else if (game_status == GAME) drawGameScreen();
	else drawEndScreen();
}

void Game::init()
{
	graphics::setFont(std::string(FONT_ASSETS_PATH) + "ARCADECLASSIC.ttf");
	graphics::playMusic(std::string(AUDIO_ASSETS_PATH) + "NCT_127-Cherry_Bomb_Instrumental.mp3", 0.9f, true, 3000);
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

	cherries.clear();
	shots.clear();
	fruits.clear();
}

void Game::drawTitleScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	br.outline_opacity = 0.0f;
	br.texture = std::string(PLAYER_ASSETS_PATH) + "cb_3.png";
	graphics::drawRect(CANVAS_WIDTH / 2, 200, 700, 400, br);

	br.texture = std::string(PLAYER_ASSETS_PATH) + "inst.png";
	graphics::drawRect(50, 50, 70, 70, br);

	float flash = 0.3f + 0.9f * sinf(graphics::getGlobalTime() / 200);
	br.fill_color[0] += flash;
	br.fill_color[1] += flash;
	br.fill_color[2] += flash;

	graphics::drawText(CANVAS_WIDTH / 2 - 240, (9 * CANVAS_HEIGHT / 10) + 15, 50, "PRESS SPACE TO START", br);

	graphics::drawText(90, 50, 28, "PRESS H", br);
	graphics::drawText(90, 70, 28, "FOR HELP", br);
}

void Game::drawInstructionScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	graphics::drawText(WINDOW_WIDTH / 2 - 140, 100, 60, "HOW TO PLAY", br);
	
	graphics::drawText(CANVAS_WIDTH/2-400, 170, 30, "USE A AND D OR LEFT AND RIGHT ARROWS TO MOVE YOUR WEAPON", br);
	graphics::drawText(CANVAS_WIDTH/2-300, 220, 30, "FIRE SHOTS BY LEFT CLICKING YOUR MOUSE", br);
	graphics::drawText(CANVAS_WIDTH/2-350, 270, 30, "BE CAREFUL! IF YOU HIT A CHERRY YOU WILL LOSE A LIFE!", br);
	graphics::drawText(CANVAS_WIDTH/2-330, 320, 30, "AIM FOR THE OTHER FRUITS AND EARN A HIGH SCORE!", br);

	float flash = 0.3f + 0.9f * sinf(graphics::getGlobalTime() / 200);
	br.fill_color[0] += flash;
	br.fill_color[1] += flash;
	br.fill_color[2] += flash;

	graphics::drawText(CANVAS_WIDTH/2-250, 450, 50, "PRESS ENTER TO GO BACK", br);
}

void Game::drawWeaponScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	graphics::drawText(100, 100, 60, "CHOOSE YOUR WEAPON", br);
	graphics::drawText(100, 150, 30, "PRESS ENTER TO CHOOSE", br);

	///draw fork
	graphics::Brush brf;
	brf.texture = std::string(PLAYER_ASSETS_PATH) + "fork.png";
	brf.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 3, 300, 140, 140, brf);

	///draw chopsticks
	graphics::Brush brc;
	brc.texture = std::string(PLAYER_ASSETS_PATH) + "chopsticks.png";
	brc.outline_opacity = 0.0f;
	graphics::drawRect(2 * CANVAS_WIDTH / 3, 300, 200, 200, brc);

	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		//choose fork
		weapon_choice = FORK;
	}

	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT))
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

	graphics::Brush br;

	//UI/info layer
	if (player)
	{
		//score
		char score[40];
		sprintf_s(score, "SCORE %i", player->getScore());
		
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		graphics::drawText(50, 60, 50, score, br);
	}
	//life
	float life = player ? player->getLife() : 0;

	br.texture = std::string(PLAYER_ASSETS_PATH) + "heart.png";
	br.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;
	br.outline_color[0] = 1.0f;
	br.outline_color[1] = 1.0f;
	br.outline_color[2] = 1.0f;
	int x = 230;
	for (int i = 0; i < life; i++)
	{
		graphics::drawRect(CANVAS_WIDTH - x, 45, 60, 60, br);
		x -= 45;
	}

	//explosion effect
	if (explosion == true)
	{
		br.texture = std::string(FRUIT_ASSETS_PATH) + "boom.png";
		br.outline_opacity = 0.0f;
		graphics::drawRect(explosion_x, explosion_y, explosion_size, explosion_size, br);

		if (graphics::getDeltaTime() > 1000)
			br.texture = "";

		explosion == false;
	}
}

void Game::drawEndScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;

	graphics::drawText((CANVAS_WIDTH / 2) - 250, 2.5 * CANVAS_HEIGHT / 10, 110, "GAME OVER", br);

	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	graphics::drawText((CANVAS_WIDTH / 2) - 105, 4 * CANVAS_HEIGHT / 10, 80, "SCORE", br);

	float flash = 0.3f + 0.9f * sinf(graphics::getGlobalTime() / 200);
	br.fill_color[0] += flash;
	br.fill_color[1] += flash;
	br.fill_color[2] += flash;

	graphics::drawText((CANVAS_WIDTH / 2) - 300, 8 * CANVAS_HEIGHT / 10, 50, "PRESS ENTER TO PLAY AGAIN", br);
	
	printScore();
}

void Game::printScore()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	char score[40];
	sprintf_s(score, "%i", player->getScore());
	
	graphics::drawText((CANVAS_WIDTH / 2) - 25, 6 * CANVAS_HEIGHT / 10, 80, score, br);
}

void Game::updateTitleScreen()
{
	if(graphics::getKeyState(graphics::SCANCODE_H))
	{
		game_status = INSTRUCTIONS;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		game_status = WEAPON;
	}
}

void Game::updateInstructionScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		game_status = TITLE;
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

	for (size_t f = 0; f < fruits.size(); f++)
		checkFruits(f);

	for (size_t c = 0;c < cherries.size(); c++)
		checkCherries(c);

	spawnFruit();

	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed)
	{
		checkShots();
		spawnShot();
	}

	if (!cherries.empty())
	{
		for (auto cherry : cherries)
		{
			cherry->update();
		}
	}

	if (!shots.empty())
	{
		for (auto shot : shots) {
			shot->update();
		}
	}

	if (!fruits.empty())
	{
		for (auto fruit : fruits)
		{
			fruit->update();
		}
	}
	
	checkTotalCherryCollision();

	checkTotalFruitCollision();

	increasefruitSpawn();
}

void Game::updateEndScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		resetPlayer();
		game_status = TITLE;
	}
}
