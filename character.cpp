#include "character.h"
#include "random.h"
#include <string>
#include <iostream>
#include <algorithm>

// Initialize the new character
void character_stats::initialize() {
	while (true) {
		std::cout << "What difficulty you want? 1 is the easiest. 2 is the middle. 3 is the hardest." << std::endl;
		std::cin >> difficulty;
		// Check user input
		if (std::cin.fail() || difficulty < 1 || difficulty > 3) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Input not recognized. Please enter a number only!" << std::endl << std::endl;
			continue;
		}
		break;
	}
	// Different stats depending on user difficulty choice
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
	// Get user name
	std::cout << "What would you name your hero?" << std::endl;
	std::cin.ignore();
	// Use getline() to prevent name with space
	std::getline(std::cin, name);
	while (name == "") {
		std::cout << "Character name cannot be empty! Please enter a name." << std::endl;
		std::cin >> name;
	}
	date = 0;
	std::cout << "Welcome! " << name << std::endl;
}

// Print all the stats of the character
void character_stats::display_stat() {
	std::cout << "HP: " << hp << "/" << hp_max << " MP: " << mp << "/" << mp_max << " ATK: " << atk << " DEF: " << def << " WIS: " << wis << " VIT: " << vit << " STA: " << stamina << "/" << sta_max << std::endl;
}

// Print all items in character inventory. e.g.: 1. Iron Armor 2. Iron Sword
void character_stats::display_inventory() {
	for (int i = 0; i < inventory.size(); i++) {
		std::cout << (i + 1) << ": " << inventory[i] << " ";
	}
	std::cout << std::endl;
}
// Return all the stats of character in 1 string
std::string character_stats::read_stat() {
	std::string return_message;
	return_message = "HP " + std::to_string(hp) + " MP " + std::to_string(mp) + " ATK " + std::to_string(atk) + " DEF " + std::to_string(def) + " WIS " + std::to_string(wis) + " VIT " + std::to_string(vit) + " STA " + std::to_string(stamina) + " HP_MAX " + std::to_string(hp_max) + " MP_MAX " + std::to_string(mp_max) + +" STA_MAX " + std::to_string(sta_max);
	return return_message;
}

// Return the value of a specific stats of character
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

// Return character name
std::string character_stats::read_name() {
	return name;
}

// Change character specific stat.
// abs is used to check if we need to directly change to specific value
bool character_stats::change_stat(std::string stat_name, int delta, bool abs) {
	if (stat_name == "HP") {
		(abs == false) ? ((hp + delta > hp_max) ? (hp = hp_max) : (hp += delta)) : (hp = delta);
		return true;
	}
	else if (stat_name == "MP") {
		(abs == false) ? ((mp + delta > mp_max) ? (mp = mp_max) : (mp += delta)) : (mp = delta);
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

// Add or remove item with item_name in inventory.
// Position only needed when removing item
// item_name only needed when adding item
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

// Change character name.
bool character_stats::change_name(std::string input_name) {
	name = input_name;
	return true;
}

// Change the equipped items of character
bool character_stats::change_equipeed(std::string action, std::string equip_name) {
	// If action == "equip", add it to the vector tracking all equipped item
	if (action == "equip") {
		equipped.push_back(equip_name);
		return true;
	}
	else {
		// Unequip
		// Find the equipped item in vector and remove it
		std::vector<std::string>::iterator position = std::find(equipped.begin(), equipped.end(), equip_name);
		if (position != equipped.end()) {
			equipped.erase(position);
			return true;
		}
		return false;
	}
}

// Search and check if the item is equipped
bool character_stats::search_equipped(std::string equip_name) {
	if (std::find(equipped.begin(), equipped.end(), equip_name) != equipped.end()) {
		// Return true if equipped
		return true;
	}
	else {
		return false;
	}
}

// Search and check if the item is in inventory
bool character_stats::search_inventory(std::string item_name) {
	if (std::find(inventory.begin(), inventory.end(), item_name) != inventory.end()) {
		return true;
	}
	else {
		return false;
	}
}

// Search the name of specific item in inventory
// Position = index + 1
std::string character_stats::search_item_name_in_inventory(int position) {
	if (position < 1 || position > inventory.size()) {
		return "";
	}
	return inventory[position - 1];
}

// Return the number of inventory items
int character_stats::inventory_size() {
	return (int)inventory.size();
}

// Search the name of specific item in equipped
// Position = index + 1
std::string character_stats::search_item_name_in_equipped(int position) {
	if (position < 1 || position > inventory.size()) {
		return "";
	}
	return inventory[position - 1];
}

// Return the number of equipped items
int character_stats::equipped_size() {
	return (int)equipped.size();
}