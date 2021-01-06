#pragma once
#include "graphics.h"
#include "Player.h"
#include "Shot.h"
#include "Fruit.h"
#include <list>
#include <vector>

class Game
{
	typedef enum { TITLE,INSTRUCTIONS, WEAPON, GAME, END } status_t;
	status_t game_status = TITLE;
	class Player* player;
	//variable to check if player has already been initialized
	bool player_initialized = false;
	bool debug_mode = false;

	typedef enum { FORK, CHOPSTICKS } choice_w;
	choice_w weapon_choice = FORK;
	
	std::list<int> scoreboard;

	//for cherries
	std::vector<Fruit*> cherries;

	//for shots
	std::vector<Shot*> shots;
	void checkShot();

	graphics::MouseState mouse;
	void spawnShot();

	//for the rest of the fruits
	std::vector<Fruit*> fruits;
	void spawnFruit();

	//fruit spawn time
	float fruitSpawnInterval = 800.0f;
	float fruitcurrentSpawnTime = 0;
	void setfruitSpawnInterval(float x) { fruitSpawnInterval = x; }
	void increasefruitSpawn();

	//shot-fruit collision
	bool checkCollision(Shot* shot, Fruit* fruit);

	void checkTotalCherryCollision();

	void checkTotalFruitCollision();

	//void updateScoreboard();
	void resetPlayer();

	void drawTitleScreen();
	void drawInstructionScreen();
	void drawWeaponScreen();
	void drawGameScreen();
	void drawEndScreen();

	void printScore();

	void updateTitleScreen();
	void updateInstructionScreen();
	void updateWeaponScreen();
	void updateGameScreen();
	void updateEndScreen();

public:
	void update();
	void draw();
	void init();
	Game();
	~Game();

	int getGameMode() const { return game_status; }
	bool getDebugMode() const { return debug_mode; }
	void setDebugMode(bool d) { debug_mode = d; }

	int getWeaponChoice() const { return weapon_choice; }
};