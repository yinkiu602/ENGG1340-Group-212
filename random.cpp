#include "random.h"
#include <ctime>
#include <cstdlib>

unsigned int random_value = 0;
int randomizer(int mod) {
	// Prevent repeatedly calling srand. Resulting in same random number generated everytime.
	if (random_value == 0) {
		random_value = (unsigned int)time(NULL);
		srand(random_value);
	}
	// We don't want to do % 0. Cahgne to 1 if mod == 0
	if (mod == 0) { mod = 1; }
	int result = rand() % mod;
	// Min value == 1 for output
	if (result == 0) { result = 1; }
	return result;
}