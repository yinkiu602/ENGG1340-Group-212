#include <iostream>
#include "character.h"
#include "saveload.h"
#include "progress.h"
#include <fstream>


int main() {
	character_stats character;
	std::string user_input;
	while (true) {
		std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top
		std::cout << "Welcome to Realms and Might. \nType \"s\" if you want to save the game at any time.\nType \"l\" if you want to load the game.\nType \"n\" to start a new game.\nType \"c\" to continue (if you loaded the save file).\nType \"e\" to exit." << std::endl;
		std::cin >> user_input;
		if (user_input == "s") {
			// character.display_stat();
			save(character);
		}
		else if (user_input == "l") {
			load(character);
			character.display_stat();
		}
		else if (user_input == "e") {
			std::string exit_confirm;
			std::cout << "Are you sure to quit? Progress will not be automatically saved! (y/n)" << std::endl;
			std::cin >> exit_confirm;
			if (exit_confirm == "y") {
				exit(0);
			}
		}
		else if (user_input == "c") {
			if (character.read_name() == "") {
				std::cout << "Character not loaded! If you just opened the game, press \"l\" to load the charater first." << std::endl;
			}
			else {
				main_story(&character);
			}
		}
		else {
			character.initialize();
			character.display_stat();
			std::cout << "Done" << std::endl;
			main_story(&character);
		}
	}
	return 0;
}