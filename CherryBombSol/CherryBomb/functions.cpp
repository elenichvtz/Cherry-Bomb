#include "functions.h"

float rand0to1() {
	return rand() / (float)RAND_MAX;
}

float rand0toN(int n)
{
	float x = rand() % (n + 1);
	return x;
}
