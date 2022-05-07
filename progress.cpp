#include "character.h"
#include "training.h"
#include "battle_system.h"
#include "shop.h"
#include "casino.h"
#include "events.h"
#include "random.h"
#include <iostream>

bool main_story(character_stats *p) {
	// Variable to help with random event.
    int randomeventdecider = randomizer(10);
	std::string user_option;
	std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top
	// Stay in the story until user explicitly request exit
	while (true) {
        std::cout << "random value of the day: " << randomeventdecider << std::endl;
		std::cout << "Day " << p->date << ". " << "Hi, " << p->read_name() << "! Such a good day today! What do you want to do? (1-6)" << std::endl;
		std::cout << "1. Train yourself" << std::endl;
		std::cout << "2. Feeling lucky, go casino" << std::endl;
		std::cout << "3. Check my character" << std::endl;
		std::cout << "4. Purchase equipments" << std::endl;
		std::cout << "5. End your day and have a good sleep." << std::endl;
		std::cout << "6. Return to main menu" << std::endl;
		std::cin >> user_option;
		// Need to fight the boss on the 30th day
		if (p->date == 30) {
			std::cout << "It's time to fight the boss. Be prepared for it!" << std::endl;
			// Call the battle system
			battle_system(p, "boss");
			// Player or boss dead
			return true;
		}
		// Train character stats
		if (user_option == "1") {
			// Decide random event
            if (randomeventdecider >= 6) {
              events(p);
              randomeventdecider = -1;
            }
			// Function to train character stats
			training(p);
			std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top
		}
		// Casino
		else if (user_option == "2") {
			if (randomeventdecider >= 6) {
				events(p);
				randomeventdecider = -1;
			}
			// Call the casino function
			casino_menu(p);
		}
		// Display the stats and inventory
		else if (user_option == "3") {
			p->display_stat();
			std::cout << std::endl;
			p->display_inventory();
			std::cout << std::endl;
		}
		// Goto the shop and purchase equip
		else if (user_option == "4") {
            if (randomeventdecider >= 6) {
              events(p);
              randomeventdecider = -1;
            }
            shop(p);
		}
		// End a day and restore the stamina to max.
		else if (user_option == "5") {
			std::cout << "\033[2J\033[1;1H";
			std::cout << "Another day passed by......" << std::endl;
            randomeventdecider = randomizer(10);
			p->date++;
			p->change_stat("STA", p->read_specific_stat("STA_MAX"), true);
		}
		// Back to main menu
		else if (user_option == "6") {
			return false;
		}
		else {
			std::cout << "Sorry. I don't get what you mean. Please input again." << std::endl;
		}
	}
}