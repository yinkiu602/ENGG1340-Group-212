#include "character.h"
#include "saveload.h"

#include <iostream>
#include <fstream>


// Check if file exist. Return false if not exist
bool checkexist(std::ifstream &stream, std::string filename) {
	// Add the file extension of save file generated from this game.
	filename += ".gamesave";
	stream.open(filename.c_str());
	// If fail == not exist
	if (stream.fail()) {
		stream.close();
		return false;
	}
	else {
		stream.close();
		return true;
	}
}

// Save game data to file. Filename: xxx.gamesave
void save(character_stats &p) {
	// Check the name of character. If name == "", no character created yet. No need save
	if (p.read_name() == "") {
		std::cout << "Cannot save! Character not yet created!" << std::endl;
		return;
	}
	std::string filename;
	std::cout << "Please specify a file name for save file." << std::endl;
	std::cin >> filename;
	// Check if exist.
	std::ifstream file_check;
	// Prompt if exist file with same name
	if (checkexist(file_check, filename)) {
		std::string user_prompt;
		while (true) {
			std::cout << "File of the same name exist. Overwrite? (y/n)" << std::endl;
			std::cin >> user_prompt;
			if (user_prompt == "y") { break; }
			if (user_prompt == "n") {
				std::cout << "Please input another file name: " << std::endl;
				std::cin >> filename;
				if (checkexist(file_check, filename)) {
					continue;
				}
				else {
					break;
				}

			}
		}
	}
	// Create output stream to output data
	std::ofstream output_stream;
	// Open the gamesave file
	output_stream.open((filename + ".gamesave").c_str());
	// Output character stats, name, game date, money, inventory items and equipped items to file.
	output_stream << p.read_stat() << std::endl;
	output_stream << p.read_name() << std::endl;
	output_stream << p.date << std::endl;
	output_stream << p.money << std::endl;
	output_stream << p.inventory_size() << std::endl;
	for (int i = 0; i < p.inventory_size(); i++) {
		output_stream << p.search_item_name_in_inventory(i + 1) << std::endl;
	}
	output_stream << p.equipped_size() << std::endl;
	for (int i = 0; i < p.equipped_size(); i++) {
		output_stream << p.search_item_name_in_equipped(i + 1) << std::endl;
	}
	// Finish writting. Close the file
	output_stream.close();
}

// Load game data from savefile
void load(character_stats &p) {
	std::string filename;
	std::cout << "Please specify the save file name." << std::endl;
	std::cin >> filename;
	std::ifstream input_stream;
	// Continue if exist
	if (checkexist(input_stream, filename)) {
		input_stream.open((filename + ".gamesave").c_str());
		// Check in case for no reason open failed?
		if (!input_stream.fail()) {
			std::string value_name, value;
			// First 10 stores the stats of character. Call change_stat() to change stats.
			for (int i = 0; i < 10; i++) {
				input_stream >> value_name >> value;
				p.change_stat(value_name, std::stoi(value), true);
			}
			// Dummy pipe to move to next line.
			std::getline(input_stream, value);
			// Get character name
			std::getline(input_stream, value);
			p.change_name(value);
			// Get game date. Change to int before assignment.
			std::getline(input_stream, value);
			p.date = std::stoi(value);
			// Get character money. Change to int before assignment.
			std::getline(input_stream, value);
			p.money = std::stoi(value);
			// Get the number of inventory items. Change to int
			std::getline(input_stream, value);
			int inventory_size = std::stoi(value);
			// Add inventory_size items to the character
			for (int i = 0; i < inventory_size; i++) {
				std::getline(input_stream, value);
				p.change_inventory("add", -1, value);
			}
			// Get the number of equipped items. Change to int
			std::getline(input_stream, value);
			int equipped_size = std::stoi(value);
			// Add equipped_size items to the character
			for (int i = 0; i < equipped_size; i++) {
				std::getline(input_stream, value);
				p.change_equipeed("equip", value);
			}
			// Close the file
			input_stream.close();
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "File not found" << std::endl;
	}

}
