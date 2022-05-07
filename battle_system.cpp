// Prototype
#include "battle_system.h"
#include "character.h"
#include "item.h"
#include "random.h"
#include <iostream>
#include <iomanip>

// Similar to the character, emeny struct to save stats. 
struct enemy {
	int hp, mp, atk, def, wis, vit;
};
// Declare the 3 types of boss and to_fight variable to save the emeny fighting.
enemy small, big, boss, to_fight;
// Save the MAX stats of the emeny
int emeny_max_hp;

// Enable only when compile in linux
// Allow message width be dynamicly change depends on console width.
#include <sys/ioctl.h>

struct winsize console_window;
int windows_width() {
	ioctl(1, TIOCGWINSZ, &console_window);
	return console_window.ws_col;
}
// End of linux only code

// Return the string of hp_bar create by the percentage of remaining hp.
std::string hp_bar(int hp, int hp_max, int width = 13) {
	return (std::string((width * hp / hp_max), '+') + std::string((width - width * hp / hp_max), '-'));
}

// Function to generate the string for printing the character name or HP message during battle.
std::string message_generation(std::string message_type, character_stats * p) {
	// Assume message box size is fixed. Max width == 15 char
	int width = 15;
	std::string output_message, message_content;
	// Generate formatted character name
	if (message_type == "name") {
		int name_length = p->read_name().length();
		// If character name is too long, print "Player" only to avoid formatting issue.
		if (name_length > 15) {
			message_content = "Player";
		}
		else {
			message_content = p->read_name();
		}

	}
	// Generate formatted character hp / max hp string.
	else if (message_type == "player_hp") {
		// Count the total legnth of hp & hp_max.
		int hp_length = std::to_string(p->read_specific_stat("HP")).length() + std::to_string(p->read_specific_stat("HP_MAX")).length();
		// Include spacing between text depending on the length calculated above
		if (hp_length > 8) {
			message_content = "HP:" + std::to_string(p->read_specific_stat("HP")) + "/" + std::to_string(p->read_specific_stat("HP_MAX"));
		}
		else {
			message_content = "HP: " + std::to_string(p->read_specific_stat("HP")) + " / " + std::to_string(p->read_specific_stat("HP_MAX"));
		}
	}
	// Generate formatted emeny hp / max hp string.
	else {
		int hp_length = std::to_string(to_fight.hp).length() + std::to_string(emeny_max_hp).length();
		if (hp_length > 8) {
			message_content = "HP:" + std::to_string(to_fight.hp) + "/" + std::to_string(emeny_max_hp);
		}
		else {
			message_content = "HP: " + std::to_string(to_fight.hp) + " / " + std::to_string(emeny_max_hp);
		}
	}
	// The stat box always start with "/"
	output_message = "/";
	// If the formatted message from above is even, we need 1 additional " " on left portion.
	if (message_content.length() % 2 == 0) { output_message += " "; }
	// FIll the gap from "/" until the text
	for (int i = 0; i < ((15 - message_content.length()) / 2); i++) {
		output_message += " ";
	}
	// Add the formatted message to the output_message
	output_message += message_content;
	// Fill the gap from text till the end of stat box.
	for (int i = 0; i < ((15 - message_content.length()) / 2); i++) {
		output_message += " ";
	}
	// The stat box ends with "/"
	output_message += "/";
	return output_message;
}


void print_entites(std::string type, character_stats* p) {
	if (type == "boss") {
		// Change from 90 to windows_width() when compile on linux
		// windows_width() used to change width dynamicly.
		std::cout << std::setw(windows_width()) << std::right << "*****************" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/     ENEMY     /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/               /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << message_generation("", p) << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/ " + hp_bar(to_fight.hp, emeny_max_hp) + " /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/               /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "*****************" << std::endl;
	}
	if (type == "player") {
		std::cout << "*****************" << std::endl;
		std::cout << message_generation("name", p) << std::endl;
		std::cout << "/               /" << std::endl;
		std::cout << message_generation("player_hp", p) << std::endl;
		std::cout << "/ " + hp_bar(p->read_specific_stat("HP"), p->read_specific_stat("HP_MAX")) + " /" << std::endl;
		std::cout << "/               /" << std::endl;
		std::cout << "*****************" << std::endl;
	}
}

void message_box() {
	// Enable when in linux
	int width = windows_width() * 0.8;
	// Print the first line: **************************
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
	// Calculate damage of player and emeny.
	int attack_damage_calculation, receive_damage_calculation;
	// Save the character stats
	int charhp, charmp, charatk, chardef, charwis, charvit;

	charhp = p->read_specific_stat("HP");
	charmp = p->read_specific_stat("MP");
	charatk = p->read_specific_stat("ATK");
	chardef = p->read_specific_stat("DEF");
	charwis = p->read_specific_stat("WIS");
	charvit = p->read_specific_stat("VIT");

	// Stats of the emeny depending on character stats
	boss = { 5000, 300, 500, 500, 350, 300 };
	small = { charhp - randomizer(charhp / 3), charmp - randomizer(charmp / 3), charatk - randomizer(charatk / 3), chardef - randomizer(chardef / 3), charwis - randomizer(charwis / 3), charvit - randomizer(charvit / 3) };
	big = { charhp + randomizer(charhp / 3), charmp + randomizer(charmp / 3), charatk + randomizer(charatk / 3), chardef + randomizer(chardef / 3), charwis + randomizer(charwis / 3), charvit + randomizer(charvit / 3) };

	// Select the emeny to fight
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
		// Print the emeny stat box at top right first
		print_entites("boss", p);
		std::cout << std::endl << std::endl << std::endl;
		// Print character stat box at bottom left.
		print_entites("player", p);
		// Print the message box containing the action.
		message_box();
		while (true) {
			std::cout << "Please indicate your next action: ";
			std::cin >> user_input;
			// Loop until user enters correctly.
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Input not recognized. Please enter a number only!" << std::endl << std::endl;
				continue;
			}
			// If correct input
			break;
		}

		// Damage calculation: Attack - defense. Defense can only neglect 80% damage. Except when user in defense mode
		// If user choose to attack
		if (user_input == 1) {
			attack_damage_calculation = p->read_specific_stat("ATK") - to_fight.def;
			if (attack_damage_calculation <= 0) { attack_damage_calculation = (int)p->read_specific_stat("ATK") * 0.2; }
			// Reduce emeny hp base on damage calculated from the formula above.
			to_fight.hp -= attack_damage_calculation;
			std::cout << "You attacked the emeny for " << attack_damage_calculation << " HP!" << std::endl;
			receive_damage_calculation = to_fight.atk - p->read_specific_stat("DEF");
			if (receive_damage_calculation <= 0) { receive_damage_calculation = to_fight.atk * 0.2; }
			std::cout << "The emeny attacked you for " << receive_damage_calculation << " HP!" << std::endl;
			// Refuce character hp base on damage calculated from above
			p->change_stat("HP", -receive_damage_calculation);
			// If any side hp <= 0, the game end
			if (p->read_specific_stat("HP") <= 0 || to_fight.hp <= 0) { ended = true; }
		}
		// Defense position for character.
		else if (user_input == 2) {
			// CHaracter defense is doubled. No 80% rule.
			receive_damage_calculation = to_fight.atk - p->read_specific_stat("DEF") * 2;
			if (receive_damage_calculation <= 0) { receive_damage_calculation = 0; }
			std::cout << "You move yourself into defend position." << std::endl;
			std::cout << "The emeny attacked you for " << receive_damage_calculation << " HP!" << std::endl;
			p->change_stat("HP", -receive_damage_calculation);
			if (p->read_specific_stat("HP") <= 0 || to_fight.hp <= 0) { ended = true; }
		}
		// Use inventory
		else {
			std::cout << "You currently have:" << std::endl;
			// Print the inventory
			p->display_inventory();
			// Check correctness of user input
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
			// Change from number to item name
			std::string item_name = p->search_item_name_in_inventory(user_input);
			// If doesnt own the item
			if (item_name == "") {
				std::cout << "You don't have the item!" << std::endl;
				continue;
			}
			// Prompt if equipped
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



