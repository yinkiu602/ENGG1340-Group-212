#include <iostream>
#include <unordered_map>
#include "character.h"
#include "random.h"
#include "training.h"

// Map to translate user int input to the stat identifier.
std::unordered_map <int, std::string> stat_converter{
	{1, "HP_MAX"},
	{2, "MP_MAX"},
	{3, "ATK"},
	{4, "DEF"},
	{5, "WIS"},
	{6, "VIT"},
	{7, "STA_MAX"}
};

void training(character_stats* p) {
	std::cout << "\033[2J\033[1;1H"; // Clean the screen
	int user_input;
	while (true) {
		std::cout << "Welcome to the training center! What stats you want to train? Enter a number." << " (Current stamina: " << p->read_specific_stat("STA") << ")" << std::endl;
		std::cout << "(1): HP (2): MP (3): ATK (4): DEF (5): WIS (6): VIT (7): STA (0): EXIT" << std::endl;
		std::cin >> user_input;
		// Check user input
		if (std::cin.fail()) {
			std::cout << "Please enter a number only." << std::endl;
			continue;
		}
		// If user choose to exit
		if (user_input == 0) { return; }
		// If == 0, the integer inputted from user is not in the map.
		if (stat_converter.count(user_input) == 0) {
			std::cout << "Input not recognized. Please reenter the number." << std::endl;
			continue;
		}
		// Randomize the chance for big success (2x increase)
		int big_success = randomizer(100);
		// Randomize the value change
		int increase = randomizer(10);
		// Training consume stamina. Min == 10
		if (p->read_specific_stat("STA") < 10) {
			std::cout << "You do not have enough stamina! Maybe take a rest?" << std::endl;
			continue;
		}
		// 20% big success
		if (big_success >= 80) {
			std::cout << "Big success! Your character earned 2X the experience!" << std::endl;
			// Print the stats before change
			std::cout << stat_converter[user_input] << ": " << p->read_specific_stat(stat_converter[user_input]) << "->";
			// Change user stats
			p->change_stat(stat_converter[user_input], increase * 2);
		}
		else {
			std::cout << stat_converter[user_input] << ": " << p->read_specific_stat(stat_converter[user_input]) << "->";
			p->change_stat(stat_converter[user_input], increase);
		}
		// Print the stats after change
		std::cout << p->read_specific_stat(stat_converter[user_input]) << std::endl;
		// Print stamina change
		std::cout << "STA: " << p->read_specific_stat("STA") << "->";
		// Reduce stamina
		p->change_stat("STA", -10);
		std::cout << p->read_specific_stat("STA") << std::endl;
	}
}