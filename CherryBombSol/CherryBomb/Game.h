#pragma once
#include "Player.h"

class Game
{
	Player* player = nullptr;
	//variable to check if player has already been initialized
	bool player_init = false;
	bool debug_mode = false;

public:
	void update();

	void draw();

	void init();

	Game();

	~Game();

	void setDebugMode(bool mode) { debug_mode = mode; }

	bool getDebugMode() { return debug_mode; }
};