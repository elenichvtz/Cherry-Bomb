#pragma once
#include "Player.h"
#include "Cherry.h"

class Game
{
	Player* player = nullptr;
	//variable to check if player has already been initialized
	bool player_init = false;
	bool debug_mode = false;
	//xreiazetai lista me ta polla cherries kai polla fruits
	Cherry* cherry = nullptr;
	//for cherries
	void spawnCherry();
	//for the rest of the fruits
	void spawnFruit();
	void checkCherry();

public:
	void update();

	void draw();

	void init();

	Game();

	~Game();

	void setDebugMode(bool mode) { debug_mode = mode; }

	bool getDebugMode() { return debug_mode; }
};