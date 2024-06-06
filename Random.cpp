/*
	David Brown
	9.6.16
	Random Number Generation
*/
	
#include <cstdlib>
#include <ctime>
#include "Random.h"

using namespace std;

void seedRandom ()
{
	srand (time(NULL));
}

int getRandomInt (int low, int high)
{
	return rand()%(high - low) + low;
}

float getRandomFloat (float low, float high)
{
	return low + static_cast<float> (rand()) / (static_cast <float> (RAND_MAX/(high - low)));
}