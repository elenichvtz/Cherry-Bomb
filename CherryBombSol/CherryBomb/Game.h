#pragma once
#include "Player.h"
#include "Cherry.h"
#include <list>
#include <vector>

class Game
{
	typedef enum { TITLE, WEAPON, GAME, END } status_t;
	status_t game_status = TITLE;
	Player* player = nullptr;
	//variable to check if player has already been initialized
	bool player_initialized = false;
	bool debug_mode = false;
	
	//xreiazetai lista me ta polla cherries kai polla fruits
	
	std::list<int> scoreboard;

	Cherry* cherry = nullptr;
	//for cherries
	void spawnCherry();
	void checkCherry();

	//for the rest of the fruits
	void spawnFruit();

	bool checkCollision();

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
	int getGameMode() { return game_status; }
	bool getDebugMode() const { return debug_mode; }
	void setDebugMode(bool d) { debug_mode = d; }

	//std::list<int> getScoreboard() { return scoreboard; }
	//void setScoreboard(std::list<int> s) { scoreboard = s; }
};