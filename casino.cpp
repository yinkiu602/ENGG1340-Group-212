#include "casino.h"
#include "character.h"
#include "blackjack.h"
#include "high-low.h"
#include <iostream>

void casino_menu(character_stats* p) {
	while (true) {
		std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top
		int user_input = -1;
		while (true) {
			std::cout << "Welcome to the casino! Wants to try out your luck today?" << std::endl;
			std::cout << "Blackjack and Hi Lo are current open!" << std::endl;
			std::cout << "To play Blackjack. Enter (1)!" << std::endl;
			std::cout << "To play Hi Lo. Enter (2)!" << std::endl;
			std::cout << "To exit the casino. Enter (3)!" << std::endl;
			std::cout << "Please enter a number: ";
			std::cin >> user_input;
			if (std::cin.fail() || user_input < 1 || user_input >3) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Input not recognized. Please enter a number only!" << std::endl << std::endl;
				continue;
			}
			break;
		}
		if (user_input == 1) {
			blackjack(p);
		}
		else if (user_input == 2) {
			high_low(p);
		}
		else {
			break;
		}
	}
}


