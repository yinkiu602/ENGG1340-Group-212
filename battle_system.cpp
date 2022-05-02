// Prototype
#include "battle_system.h"
#include "character.h"

#include <iostream>
#include <iomanip>
#include <string>

// Enable only when compile in linux
#include <sys/ioctl.h>



// Enable only when compile in linux
struct winsize console_window;
// Enable only when compile in linux
int windows_width() {
	ioctl(1, TIOCGWINSZ, &console_window);
	return console_window.ws_col;

}

std::string hp_bar(int hp, int hp_max, int width = 13) {
	return (std::string((width * hp / hp_max), '+') + std::string((width - width * hp / hp_max), '-'));
}


void print_entites(std::string type) {
	if (type == "boss") {
		// Change from 90 to windows_width() when compile on linux
		std::cout << std::setw(windows_width()) << std::right << "*****************" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/     BOSS1     /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/               /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/  HP: 50 / 50  /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/ " + hp_bar(50, 50) + " /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/               /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "*****************" << std::endl;
	}
	if (type == "player") {
		std::cout << "*****************" << std::endl;
		std::cout << "/     User1     /" << std::endl;
		std::cout << "/               /" << std::endl;
		std::cout << "/  HP: 50 / 50  /" << std::endl;
		std::cout << "/ " + hp_bar(13, 50) + " /" << std::endl;
		std::cout << "/               /" << std::endl;
		std::cout << "*****************" << std::endl;
	}
}

void message_box() {
	// Enable when in linux
	int width = windows_width() * 0.8;
	// Print the first line
	for (int i = 0; i < (int) ((windows_width() - width) / 2); i++) {
		std::cout << " ";
	}
	for (int i = 0; i < width; i++) {
		std::cout << "*";
	}
	std::cout << std::endl;

	//print middle

	


	// Print last lime
	for (int i = 0; i < (int)((windows_width() - width) / 2); i++) {
		std::cout << " ";
	}
	for (int i = 0; i < width; i++) {
		std::cout << "*";
	}
	std::cout << std::endl;
}

bool damage_calculation(character_stats* p, std::string entity_type, std::string stat_name, int hp) {
	if (entity_type == "boss") {
		
	}
	else {
		p->change_stat(stat_name, hp);
		if (p->read_specific_stat("HP") <= 0) {
			return false;
		}
	}



}
bool battle_system(character_stats* p) {
	bool ended = false;
	//while (!ended) {
		
	//}
	std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top
	print_entites("boss");
	std::cout << std::endl << std::endl << std::endl;
	print_entites("player");
	message_box();
	return true;
}


