#pragma once
#include "graphics.h"
#include "Player.h"
#include "Cherry.h"
#include "Fruit.h"
#include <list>
#include <vector>

class Game
{
	typedef enum { TITLE, WEAPON, GAME, END } status_t;
	status_t game_status = TITLE;
	class Player* player;
	//variable to check if player has already been initialized
	bool player_initialized = false;
	bool debug_mode = false;

	typedef enum { FORK, CHOPSTICKS } choice_w;
	choice_w weapon_choice = FORK;
	
	std::list<int> scoreboard;

	//for cherries
	std::vector<Cherry*> cherries;
	void spawnCherry();
	//void checkCherry();

	//cherry spawn time
	float cherrySpawnInterval = 2000.0f;
	float cherrycurrentSpawnTime = 0;

	//for shots
	std::vector<Shot*> shots;
	void checkShot();

	class graphics::MouseState mouse;
	void spawnShot();

	//xreiazetai lista me ta polla fruits
	//for the rest of the fruits
	std::vector<Fruit*> fruits;
	void spawnFruit();

	//fruit spawn time
	float fruitSpawnInterval = 800.0f;
	float fruitcurrentSpawnTime = 0;

	//shot-cherry collision
	bool checkCollision(Shot* shot, Cherry* cherry);

	//shot-fruit collision
	bool checkCollision(Shot* shot, Fruit* fruit);

	void checkTotalCherryCollision();

	void checkTotalFruitCollision();

	void updateScoreboard();
	void resetPlayer();

	void drawTitleScreen();
	void drawWeaponScreen();
	void drawGameScreen();
	void drawEndScreen();

	void updateTitleScreen();
	void updateWeaponScreen();
	void updateGameScreen();
	void updateEndScreen();

public:
	void update();
	void draw();
	void init();
	Game();
	~Game();

	//std::vector<Cherry*> getCherries() { return cherries; }
	//std::vector<Shot*> getShots() { return shots; }

	int getGameMode() const { return game_status; }
	bool getDebugMode() const { return debug_mode; }
	void setDebugMode(bool d) { debug_mode = d; }

	int getWeaponChoice() const { return weapon_choice; }

	//std::list<int> getScoreboard() { return scoreboard; }
	//void setScoreboard(std::list<int> s) { scoreboard = s; }
};