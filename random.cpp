#include "random.h"
#include <ctime>
#include <cstdlib>

int randomizer(int mod) {
	srand((unsigned int)time(0));
	return (rand() % mod);
}