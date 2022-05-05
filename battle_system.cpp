// Prototype
#include "battle_system.h"
#include "character.h"
#include "item.h"
#include "random.h"
#include <iostream>
#include <iomanip>
#include <string>

struct enemy {
	int hp, mp, atk, def, wis, vit;
};
enemy small, big, boss, to_fight;
int charhp, charmp, charatk, chardef, charwis, charvit, emeny_max_hp;
int attack_damage_calculation, receive_damage_calculation;

// Enable only when compile in linux
#include <sys/ioctl.h>



// Enable only when compile in linux
struct winsize console_window;
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
		std::cout << std::setw(windows_width()) << std::right << "/     ENEMY     /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/               /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/  HP: 50 / 50  /" << std::endl;
		//std::cout << std::setw(windows_width()) << std::right << "/HP: " << to_fight.hp << " / " << emeny_max_hp << " /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/ " + hp_bar(to_fight.hp, emeny_max_hp) + " /" << std::endl;
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
	for (int i = 0; i < (int)((windows_width() - width) / 2); i++) {
		std::cout << " ";
	}
	for (int i = 0; i < width; i++) {
		std::cout << "*";
	}
	std::cout << std::endl;

	//print middle
	for (int i = 0; i < (int)((windows_width() - width) / 2); i++) {
		std::cout << " ";
	}
	std::cout << "*";
	for (int i = 0; i < (int)(width - 18) / 2; i++) {
		std::cout << " ";
	}
	std::cout << "1. Attack the boss";
	for (int i = 0; i < (int)(width - 18) / 2 - 1; i++) {
		std::cout << " ";
	}
	std::cout << "*" << std::endl;
	for (int i = 0; i < (int)((windows_width() - width) / 2); i++) {
		std::cout << " ";
	}
	std::cout << "*";
	for (int i = 0; i < (int)(width - 20) / 2; i++) {
		std::cout << " ";
	}
	std::cout << "2. Defend the attack";
	for (int i = 0; i < (int)(width - 20) / 2 - 1; i++) {
		std::cout << " ";
	}
	std::cout << "*" << std::endl;
	for (int i = 0; i < (int)((windows_width() - width) / 2); i++) {
		std::cout << " ";
	}
	std::cout << "*";
	for (int i = 0; i < (int)(width - 19) / 2-1; i++) {
		std::cout << " ";
	}
	std::cout << "3. Change equipment";
	for (int i = 0; i < (int)(width - 19) / 2 - 1; i++) {
		std::cout << " ";
	}
	std::cout << "*" << std::endl;


	// Print last lime
	for (int i = 0; i < (int)((windows_width() - width) / 2); i++) {
		std::cout << " ";
	}
	for (int i = 0; i < width; i++) {
		std::cout << "*";
	}
	std::cout << std::endl;
}

bool battle_system(character_stats* p, std::string enemy_name) {
	charhp = p->read_specific_stat("HP");
	charmp = p->read_specific_stat("MP");
	charatk = p->read_specific_stat("ATK");
	chardef = p->read_specific_stat("DEF");
	charwis = p->read_specific_stat("WIS");
	charvit = p->read_specific_stat("VIT");

	boss = { 5000, 300, 500, 500, 350, 300 };
	small = { charhp - randomizer(charhp / 3), charmp - randomizer(charmp / 3), charatk - randomizer(charatk / 3), chardef - randomizer(chardef / 3), charwis - randomizer(charwis / 3), charvit - randomizer(charvit / 3) };
	big = { charhp + randomizer(charhp / 3), charmp + randomizer(charmp / 3), charatk + randomizer(charatk / 3), chardef + randomizer(chardef / 3), charwis + randomizer(charwis / 3), charvit + randomizer(charvit / 3) };

	if (enemy_name == "small") {
		to_fight = small;
		emeny_max_hp = small.hp;
	}
	else if (enemy_name == "big") {
		to_fight = big;
		emeny_max_hp = big.hp;
	}
	else {
		to_fight = boss;
		emeny_max_hp = boss.hp;
	}

	bool ended = false;
	int user_input;
	std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top
	while (!ended) {
		print_entites("boss");
		std::cout << std::endl << std::endl << std::endl;
		print_entites("player");
		message_box();
		while (true) {
			std::cout << "Please indicate your next action: ";
			std::cin >> user_input;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Input not recognized. Please enter a number only!" << std::endl << std::endl;
				continue;
			}
			// If correct input
			break;
		}
		if (user_input == 1) {
			attack_damage_calculation = p->read_specific_stat("ATK") - to_fight.def;
			if (attack_damage_calculation <= 0) { attack_damage_calculation = 0; }
			to_fight.hp -= attack_damage_calculation;
			std::cout << "You attacked the emeny for " << attack_damage_calculation << " HP!" << std::endl;
			receive_damage_calculation = to_fight.atk - p->read_specific_stat("DEF");
			if (receive_damage_calculation <= 0) { receive_damage_calculation = 0; }
			std::cout << "The emeny attacked you for " << receive_damage_calculation << " HP!" << std::endl;
			p->change_stat("HP", -receive_damage_calculation);
			if (p->read_specific_stat("HP") <= 0 || to_fight.hp <= 0) { ended = true; }
		}
		else if (user_input == 2) {
			receive_damage_calculation = to_fight.atk - p->read_specific_stat("DEF") * 2;
			if (receive_damage_calculation <= 0) { receive_damage_calculation = 0; }
			std::cout << "You move yourself into defend position." << std::endl;
			std::cout << "The emeny attacked you for " << receive_damage_calculation << " HP!" << std::endl;
			p->change_stat("HP", -receive_damage_calculation);
			if (p->read_specific_stat("HP") <= 0 || to_fight.hp <= 0) { ended = true; }
		}
		else {
			std::cout << "You currently have:" << std::endl;
			p->display_inventory();
			while (true) {
				std::cout << "Which item you want to use? ";;
				std::cin >> user_input;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "Input not recognized. Please enter a number only!" << std::endl << std::endl;
					continue;
				}
				// If correct input
				break;
			}
			std::string item_name = p->search_item_name_in_inventory(user_input);
			if (item_name == "") {
				std::cout << "You don't have the item!" << std::endl;
				continue;
			}
			if (p->search_equipped(item_name)) {
				std::cout << "Equipment in use. Do you want to unequip it?" << std::endl;
				std::cout << "Enter (1) if you want to unequip" << std::endl;
				std::cout << "Enter (2) if you want to do nothing" << std::endl;
				std::cin >> user_input;
				if (user_input == 1) {
					equip(p, "", item_name);
				}
			}
			else {
				std::cout << "Equipped " << item_name << std::endl;
				std::cout << "Your original stats: " << p->read_stat() << std::endl;
				equip(p, "equip", item_name);
				std::cout << "Your new stats:      " << p->read_stat() << std::endl;

			}
		}
	}
	return true;
}



