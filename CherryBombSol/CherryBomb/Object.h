#pragma once
#include "functions.h"

class Collidable
{
public:
	virtual Disk getCollisionHull() const = 0;
};

class Object
{
protected:
	const class Game& game;
	//we use the instance of an already existing game 
public:
	Object(const class Game& game);
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};