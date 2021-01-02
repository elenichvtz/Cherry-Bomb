#pragma once
#include "Player.h"
#include "Cherry.h"
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
	std::vector<Shot*> shots;

	void spawnCherry();
	//void checkCherry();

	class graphics::MouseState mouse;

	//cherry spawn time
	float cherrySpawnInterval = 1000.0f;
	float currentSpawnTime = 0;

	//xreiazetai lista me ta polla fruits
	//for the rest of the fruits
	void spawnFruit();

	void checkShot(); /////////
	void spawnShot(); /////////

	bool checkCollision(Shot* shot, Cherry* cherry);

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