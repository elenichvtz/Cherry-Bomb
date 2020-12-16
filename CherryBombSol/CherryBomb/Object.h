#pragma once

class Object
{
	const class Game& game;
public:
	Object(const class Game& game);

	virtual void update() = 0;

	virtual void draw() = 0;

	virtual void init() = 0;
};