#include <iostream>
#include <unordered_map>
#include "character.h"
#include "random.h"
#include "training.h"


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
	std::cout << "\033[2J\033[1;1H";
	int user_input;
	while (true) {
		std::cout << "Welcome to the training center! What stats you want to train? Enter a number." << " (Current stamina: " << p->read_specific_stat("STA") << ")" << std::endl;
		std::cout << "(1): HP (2): MP (3): ATK (4): DEF (5): WIS (6): VIT (7): STA (0): EXIT" << std::endl;
		std::cin >> user_input;
		if (std::cin.fail()) {
			std::cout << "Please enter a number only." << std::endl;
			continue;
		}
		if (user_input == 0) { return; }
		if (stat_converter.count(user_input) == 0) {
			std::cout << "Input not recognized. Please reenter the number." << std::endl;
			continue;
		}
		int big_success = randomizer(100);
		int increase = randomizer(10);
		if (p->read_specific_stat("STA") < 10) {
			std::cout << "You do not have enough stamina! Maybe take a rest?" << std::endl;
			continue;
		}
		if (big_success >= 80) {
			std::cout << "Big success! Your character earned 2X the experience!" << std::endl;
			std::cout << stat_converter[user_input] << ": " << p->read_specific_stat(stat_converter[user_input]) << "->";
			p->change_stat(stat_converter[user_input], increase * 2);
		}
		else {
			std::cout << stat_converter[user_input] << ": " << p->read_specific_stat(stat_converter[user_input]) << "->";
			p->change_stat(stat_converter[user_input], increase);
		}
		std::cout << p->read_specific_stat(stat_converter[user_input]) << std::endl;
		std::cout << "STA: " << p->read_specific_stat("STA") << "->";
		p->change_stat("STA", -10);
		std::cout << p->read_specific_stat("STA") << std::endl;
	}
}