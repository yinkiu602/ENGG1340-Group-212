#include <iostream>
#include "character.h"
#include "saveload.h"
#include "progress.h"
#include <fstream>


int main() {
	// The character used in this game from character.h
	character_stats character;
	// Variable to store user input
	std::string user_input;
	// Check if finish the boss battle
	bool finish_state = false;
	while (true) {
		// End the game if boss is killed / character kill by boss
		if (finish_state == true) { break; }
		std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top
		std::cout << "Welcome to Realms and Might. \nType \"s\" if you want to save the game at any time.\nType \"l\" if you want to load the game.\nType \"n\" to start a new game.\nType \"c\" to continue (if you loaded the save file).\nType \"e\" to exit." << std::endl;
		std::cin >> user_input;
		// Call the save function
		if (user_input == "s") {
			save(character);
		}
		// Load the character from save file
		else if (user_input == "l") {
			load(character);
			character.display_stat();
		}
		// Exit the game
		else if (user_input == "e") {
			std::string exit_confirm;
			std::cout << "Are you sure to quit? Progress will not be automatically saved! (y/n)" << std::endl;
			std::cin >> exit_confirm;
			if (exit_confirm == "y") {
				exit(0);
			}
		}
		// Continue the game
		else if (user_input == "c") {
			// Check if character load or exist. character.read_name() == "" means not created/loaded.
			if (character.read_name() == "") {
				std::cout << "Character not loaded! If you just opened the game, press \"l\" to load the charater first." << std::endl;
			}
			else {
				// Prevent loading the story if exited from boss battle.
				if (!finish_state) {
					finish_state = main_story(&character);
				}
			}
		}
		else {
			// Create the character
			character.initialize();
			// Display the stats
			character.display_stat();
			finish_state = main_story(&character);
		}
	}
	// Only called if entered the boss battle. Character hp <= 0 == dead
	if (character.read_specific_stat("HP") <= 0) {
		std::cout << "Sadly you were killed. Try harder next time" << std::endl;
	}
	else {
		std::cout << "Congratulations, you have killed the boss. Try a different difficulty if you want to challenge yourself!" << std::endl;
	}
	return 0;
}