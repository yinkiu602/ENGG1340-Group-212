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
//#include <sys/ioctl.h>



// Enable only when compile in linux
struct winsize console_window;
int windows_width() {
	ioctl(1, TIOCGWINSZ, &console_window);
	return console_window.ws_col;

std::string hp_bar(int hp, int hp_max, int width = 13) {
	return (std::string((width * hp / hp_max), '+') + std::string((width - width * hp / hp_max), '-'));
}


void print_entites(std::string type) {
	if (type == "boss") {
		// Change from 90 to windows_width() when compile on linux
		std::cout << std::setw(windows_width()) << std::right << "*****************" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/     ENEMY     /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/               /" << std::endl;
		//std::cout << std::setw(windows_width()) << std::right << "/  HP: 50 / 50  /" << std::endl;
		std::cout << std::setw(windows_width()) << std::right << "/HP: " << to_fight.hp << " / " << emeny_max_hp << " /" << std::endl;
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
	for (int i = 0; i < (int) ((windows_width() - width) / 2); i++) {
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
	for (int i = 0; i < (int)(width - 18) / 2 -1; i++) {
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
	for (int i = 0; i < (int)(width - 19) / 2; i++) {
		std::cout << " ";
	}
	std::cout << "3. Change equipment";
	for (int i = 0; i < (int)(width - 19) / 2-1; i++) {
		std::cout << " ";
	}
	std::cout << "*" << std::endl;
	
	
	// Print last lime
	//for (int i = 0; i < (int)((windows_width() - width) / 2); i++) {
	//	std::cout << " ";
	//}
	//for (int i = 0; i < width; i++) {
	//	std::cout << "*";
	//}
	//std::cout << std::endl;
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
bool battle_system(character_stats* p, std::string enemy_name) {
	charhp	= p->read_specific_stat("HP");
	charmp	= p->read_specific_stat("MP");
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
	print_entites("boss");
	std::cout << std::endl << std::endl << std::endl;
	print_entites("player");
	message_box();
	return true;
}



