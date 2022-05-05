#include "character.h"
#include "saveload.h"

#include <iostream>
#include <fstream>

// File format:

bool checkexist(std::ifstream &stream, std::string filename) {
	filename += ".gamesave";
	stream.open(filename.c_str());
	if (stream.fail()) {
		stream.close();
		return false;
	}
	else {
		stream.close();
		return true;
	}
}

void save(character_stats &p) {
	if (p.read_name() == "") {
		std::cout << "Cannot save! Character not yet created!" << std::endl;
		return;
	}
	std::string filename;
	std::cout << "Please specify a file name for save file." << std::endl;
	std::cin >> filename;
	// Check if exist.
	std::ifstream file_check;
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
	std::ofstream output_stream;
	output_stream.open((filename + ".gamesave").c_str());
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
	output_stream.close();
}


void load(character_stats &p) {
	std::string filename;
	std::cout << "Please specify the save file name." << std::endl;
	std::cin >> filename;
	std::ifstream input_stream;
	if (checkexist(input_stream, filename)) {
		input_stream.open((filename + ".gamesave").c_str());
		std::vector<std::string> input_content;
		// Check in case for no reason open failed?
		if (!input_stream.fail()) {
			std::string value_name, value;
			for (int i = 0; i < 10; i++) {
				input_stream >> value_name >> value;
				p.change_stat(value_name, std::stoi(value), true);
			}
			// Dummy pipe to move to next line.
			std::getline(input_stream, value);
			std::getline(input_stream, value);
			p.change_name(value);
			std::getline(input_stream, value);
			p.date = stoi(value);
			std::getline(input_stream, value);
			p.money = stoi(value);
			std::getline(input_stream, value);
			int inventory_size = stoi(value);
			for (int i = 0; i < inventory_size; i++) {
				std::getline(input_stream, value);
				p.change_inventory("add", -1, value);
			}
			std::getline(input_stream, value);
			int equipped_size = stoi(value);
			for (int i = 0; i < equipped_size; i++) {
				std::getline(input_stream, value);
				p.change_inventory("equip", value);
			}
			input_stream.close();
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "File not found" << std::endl;
	}

}
