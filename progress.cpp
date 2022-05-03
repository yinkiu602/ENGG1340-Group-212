#include "character.h"
#include "training.h"
#include "battle_system.h"
#include "shop.h"
#include "casino.h"
#include <iostream>

void main_story(character_stats *p) {
	int time = 8;
	std::string user_option;
	std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top

	std::cout << "Day " << p->date << ". " << "Hi, " << p->read_name() << "! Such a good day today! What do you want to do? (1-6)" << std::endl;
	while (true) {
		std::cout << p->date << std::endl;
		std::cout << "1. Train yourself" << std::endl;
		std::cout << "2. Feeling lucky, go casino" << std::endl;
		std::cout << "3. Check my character" << std::endl;
		std::cout << "4. Purchase equipments" << std::endl;
		std::cout << "5. End your day and have a good sleep." << std::endl;
		std::cout << "6. Return to main menu" << std::endl;
		std::cin >> user_option;
		if (user_option == "1") {
			training(p);
			std::cout << "\033[2J\033[1;1H";
		}
		else if (user_option == "2") {
			casino_menu(p);
			//battle_system(p);
		}
		else if (user_option == "3") {
			p->display_stat();
			std::cout << std::endl;
			p->display_inventory();
			std::cout << std::endl;
		}
		else if (user_option == "4") {
            shop(p);
		}
		else if (user_option == "5") {
			p->date++;
			p->change_stat("STA", p->read_specific_stat("STA_MAX"), true);
		}
		else if (user_option == "6") {
			break;
		}
		else {
			std::cout << "Sorry. I don't get what you mean. Please input again." << std::endl;
		}
	}
}