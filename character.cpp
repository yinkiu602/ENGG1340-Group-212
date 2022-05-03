#include "character.h"
#include "random.h"
#include <string>
#include <iostream>


void character_stats::initialize() {
	while (true) {
		std::cout << "What difficulty you want? 1 is the easiest. 2 is the middle. 3 is the hardest." << std::endl;
		std::cin >> difficulty;
		if (std::cin.fail() || difficulty < 1 || difficulty > 3) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Input not recognized. Please enter a number only!" << std::endl << std::endl;
			continue;
		}
		break;
	}

	if (difficulty == 1) {
		hp = 50;
		hp_max = hp;
		mp = 50;
		mp_max = mp;
		atk = randomizer(10);
		def = randomizer(10);
		wis = randomizer(10);
		vit = randomizer(10);
	}
	else if (difficulty == 2) {
		hp = 40;
		hp_max = hp;
		mp = 40;
		mp_max = mp;
		atk = randomizer(8);
		def = randomizer(8);
		wis = randomizer(8);
		vit = randomizer(8);
	}
	else if (difficulty == 3) {
		hp = 25;
		hp_max = hp;
		mp = 25;
		mp_max = mp;
		atk = randomizer(5);
		def = randomizer(5);
		wis = randomizer(5);
		vit = randomizer(5);
	}
	stamina = 100;
	std::cout << "What would you name your hero?" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, name);
	while (name == "") {
		std::cout << "Character name cannot be empty! Please enter a name." << std::endl;
		std::cin >> name;
	}
	date = 0;
	std::cout << "Welcome! " << name << std::endl;
}

void character_stats::display_stat() {
	std::cout << "HP: " << hp  <<  "/" << hp_max << " MP: " << mp << "/" << mp_max << " ATK: " << atk << " DEF: " << def << " WIS: " << wis << " VIT: " << vit << " STA: " << stamina << "/" << sta_max << std::endl;
}

void character_stats::display_inventory() {
	for (int i = 0; i < inventory.size(); i++) {
		std::cout << (i + 1) << ": " << inventory[i] << " ";
	}
	std::cout << std::endl;
}

std::string character_stats::read_stat() {
	std::string return_message;
	return_message = "HP " + std::to_string(hp) + " MP " + std::to_string(mp) + " ATK " + std::to_string(atk) + " DEF " + std::to_string(def) + " WIS " + std::to_string(wis) + " VIT " + std::to_string(vit) + " STA " + std::to_string(stamina) + " HP_MAX " + std::to_string(hp_max) + " MP_MAX " + std::to_string(mp_max) + +" STA_MAX " + std::to_string(sta_max);
	return return_message;
}

int character_stats::read_specific_stat(std::string stat_name) {
	if (stat_name == "HP") {
		return hp;
	}
	else if (stat_name == "MP") {
		return mp;
	}
	else if (stat_name == "ATK") {
		return atk;
	}
	else if (stat_name == "DEF") {
		return def;
	}
	else if (stat_name == "WIS") {
		return wis;
	}
	else if (stat_name == "VIT") {
		return vit;
	}
	else if (stat_name == "STA") {
		return stamina;
	}
	else if (stat_name == "HP_MAX") {
		return hp_max;
	}
	else if (stat_name == "MP_MAX") {
		return mp_max;
	}
	else if (stat_name == "STA_MAX") {
		return sta_max;
	}
}
std::string character_stats::read_name() {
	return name;
}

bool character_stats::change_stat(std::string stat_name, int delta, bool abs) {
	if (stat_name == "HP") {
		(abs == false) ? (hp += delta) : (hp = delta);
		return true;
	}
	else if (stat_name == "MP") {
		(abs == false) ? (mp += delta) : (mp = delta);
		return true;
	}
	else if (stat_name == "ATK") {
		(abs == false) ? (atk += delta) : (atk = delta);
		return true;
	}
	else if (stat_name == "DEF") {
		(abs == false) ? (def += delta) : (def = delta);
		return true;
	}
	else if (stat_name == "WIS") {
		(abs == false) ? (wis += delta) : (wis = delta);
		return true;
	}
	else if (stat_name == "VIT") {
		(abs == false) ? (vit += delta) : (vit = delta);
		return true;
	}
	else if (stat_name == "STA") {
		(abs == false) ? (stamina += delta) : (stamina = delta);
		return true;
	}
	else if (stat_name == "HP_MAX") {
		(abs == false) ? (hp_max += delta, hp += delta) : (hp_max = delta);
		return true;
	}
	else if (stat_name == "MP_MAX") {
		(abs == false) ? (mp_max += delta, mp += delta) : (mp_max = delta);
		return true;
	}
	else if (stat_name == "STA_MAX") {
		(abs == false) ? (sta_max += delta, stamina += delta) : (sta_max = delta);
		return true;
	}
	else {
		return false;
	}
}

bool character_stats::change_inventory(std::string action, int position, std::string item_name) {
	if (action == "add") {
		inventory.push_back(item_name);
		return true;
	}
	else if (action == "remove") {
		inventory.erase(inventory.begin() + position);
		return true;
	}
	else {
		return false;
	}
}

bool character_stats::change_name(std::string input_name) {
	name = input_name;
	return true;
}

bool character_stats::change_equipeed(std::string action, int index) {
	if (action == "equip") {
		equipped.push_back(index);
		return true;
	}
	else {
		equipped.erase(equipped.begin() + index);
		return true;
	}
}