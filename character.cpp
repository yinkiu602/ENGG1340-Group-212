#include "character.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

void character_stats::initialize() {
	std::cout << "What difficulty you want? 1 is the easiest. 2 is the middle. 3 is the hardest." << std::endl;
	std::cin >> difficulty;
	srand((unsigned int) time(0));
	if (difficulty == 1) {
		hp = 50;
		mp = 50;
		atk = rand() % 10;
		def = rand() % 10;
		wis = rand() % 10;
		vit = rand() % 10;
	}
	else if (difficulty == 2) {
		hp = 40;
		mp = 40;
		atk = rand() % 8;
		def = rand() % 8;
		wis = rand() % 8;
		vit = rand() % 8;
	}
	else if (difficulty == 3) {
		hp = 25;
		mp = 25;
		atk = rand() % 5;
		def = rand() % 5;
		wis = rand() % 5;
		vit = rand() % 5;
	}
	stamina = 100;
	std::cout << "What would you name your hero?" << std::endl;
	std::cin >> name;
	while (name == "") {
		std::cout << "Character name cannot be empty! Please enter a name." << std::endl;
		std::cin >> name;
	}
	std::cout << "Welcome! " << name << std::endl;
}

void character_stats::display_stat() {
	std::cout << "HP: " << hp << " MP: " << mp << " ATK: " << atk << " DEF: " << def << " WIS: " << wis << " VIT: " << vit << " STA: " << stamina << std::endl;
}

void character_stats::display_inventory() {
	for (int i = 0; i < inventory.size(); i++) {
		std::cout << (i + 1) << ": " << inventory[i] << " ";
	}
	std::cout << std::endl;
}

std::string character_stats::read_stat() {
	std::string return_message;
	return_message = "HP " + std::to_string(hp) + " MP " + std::to_string(mp) + " ATK " + std::to_string(atk) + " DEF " + std::to_string(def) + " WIS " + std::to_string(wis) + " VIT " + std::to_string(vit) + " STA " + std::to_string(stamina);
	return return_message;
}

std::string character_stats::read_name() {
	return name;
}

bool character_stats::change_stat(std::string stat_name, int delta, bool abs = false) {
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