#include "functions.h"
//#include <iostream>

float rand0to1() {
	return rand() / (float)RAND_MAX;
}

float rand0to6()
{
	float x = rand() % 7;
	//std::cout << "f %f"<<x;
	return x;
}

float rand0or1()
{
	float x = rand() % 2;
	//std::cout << "f %f"<<x;
	return x;
}
