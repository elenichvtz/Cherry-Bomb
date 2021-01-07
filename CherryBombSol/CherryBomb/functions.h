#pragma once
#include <random>

float rand0to1();

float rand0toN(int n);

struct Disk 
{
	float cx, cy;
	float radius;
};