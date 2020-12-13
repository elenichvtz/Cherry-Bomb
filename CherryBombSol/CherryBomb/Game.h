#pragma once
#include "Player.h"

class Game
{
	Player* player = nullptr;
	//variable to check if player has already been initialized
	bool player_init = false;

public:
	void update();

	void draw();

	void init();

	Game();

	~Game();
};