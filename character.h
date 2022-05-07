#ifndef character_h
#define character_h

#include <string>
#include <vector>

class character_stats {
public:
	void initialize();
	void display_stat();
	void display_inventory();
	std::string read_stat();
	std::string read_name();
	bool change_stat(std::string stat_name, int delta, bool abs = false);
	int read_specific_stat(std::string stat_name);
	bool change_inventory(std::string action, int position, std::string item_name);
	bool change_equipeed(std::string action, std::string equip_name);
	bool change_name(std::string input_name);
	bool search_equipped(std::string equip_name);
	bool search_inventory(std::string item_name);
	std::string search_item_name_in_inventory(int position);
	std::string search_item_name_in_equipped(int position);
	int inventory_size();
	int equipped_size();
	int date = 0;		// Date of the game progress
	int money = 100;	// Money of character. Initial amount = 100 for all difficulty
private:
	int hp, mp, atk, def, wis, vit, stamina, difficulty; // Variable to store different stats for character and different
	int hp_max, mp_max, sta_max = 100;					 // Store the max value of character.
	std::string name = "";								 // Name of character
	std::vector<std::string> inventory;					 // Vector to store inventory item
	std::vector<std::string> equipped;					 // Vector to store equipped item
};

#endif