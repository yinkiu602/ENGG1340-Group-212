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
		bool change_stat(std::string stat_name, int delta, bool abs);
		bool change_inventory(std::string action, int position, std::string item_name);
		bool change_name(std::string input_name);
	private:
		int hp, mp, atk, def, wis, vit, stamina, difficulty;
		std::string name = "";
		std::vector<std::string> inventory;
};



#endif