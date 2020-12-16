#pragma once
#include <random>

//return a float between 0 and 1
float rand0to1(){
	return rand() / (float)RAND_MAX;
}