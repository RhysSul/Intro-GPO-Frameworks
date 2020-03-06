#include "GPRO-FW-3000\random.h"
#include <random>
#include <time.h>
int getRandomNumberInRange(int lowest, int highest)
{
	srand(time(0));
	return  (rand() % (highest - lowest + 1));
}
