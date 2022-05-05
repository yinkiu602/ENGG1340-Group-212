#include <iostream>
#include <random>
#include "character.h"
#include "random.h"

std::random_device randomiser;
std::mt19937 generator(randomiser());
std::uniform_int_distribution<> range(0, 3);

struct item {
  std::string name;
  std::string type; // distinguish the item by using type variable (equipment/consumable)
  int atk, def, wis, vit, sta;
  int stock;
  int price;
};

item legendaryItem[4] {
    {"Kodai Wand", "equipment", 0, 0, 125, 10, 0, 1, 10000},
    {"Ancestral Robe", "equipment", 0, 25, 75, 10, 5, 1, 10000},
    {"Ghrazi Rapier", "equipment", 150, 0, 0, 10, 5, 1, 10000},
    {"Justiciar Armor", "equipment", 0, 250, 0, 5, -20, 1, 10000},
};

void mysteriousMan(character_stats* p) {
    std::cout << "Hello stranger, I have some goodies here, would you want to take a look?" << std::endl;
    item itemSelling = legendaryItem[range(generator)];
    std::cout << "[0] Quit" << std::endl;
    std::cout << "[1] " << itemSelling.name << ": $" << itemSelling.price << " {";
    if (itemSelling.atk != 0) {
        std::cout << "atk: " << itemSelling.atk << ", ";
    }
    if (itemSelling.def != 0) {
        std::cout << "def: " << itemSelling.def << ", ";
    }
    if (itemSelling.wis != 0) {
        std::cout << "wis: " << itemSelling.wis << ", ";
    }
    if (itemSelling.vit != 0) {
        std::cout << "vit: " << itemSelling.vit << ", ";
    }
    if (itemSelling.sta != 0) {
        std::cout << "sta: " << itemSelling.sta << ", ";
    }
    std::cout << "stock: " << itemSelling.stock << "}" << std::endl;
    int itemDecider;
    std::cin >> itemDecider;
    while ((itemDecider != 0) || (itemDecider != 1)) {
        if (itemDecider == 0) {
            std::cout << "You did not buy anything from him." << std::endl;
            break;
        }
        else if (itemDecider == 1) {
            std::cout << "You have bought " << itemSelling.name << "!" << std::endl;
            break;
        }
        std::cout << "Invalid option!" << std::endl;
        std::cin >> itemDecider;
    }
}

void addRandomStat(character_stats* p) {
    std::string statname[5] = { "ATK", "DEF", "WIS", "STA", "VIT" };
    int statadddecider = randomizer(5);
    p->change_stat(statname[statadddecider], 5);
    std::cout << "You felt a warm pulse inside you, you think you have understood something. (" << statname[statadddecider] << " increased)" << std::endl;
}

void beggar(character_stats* p) {
    std::cout << "As you walked down the road, you see a beggar begging for money..." << std::endl;
    std::cout << "Goodday sir, would you mind sparing me a few clangs?" << std::endl;
    std::cout << "[0] Quit" << std::endl << "[1] Give him $100" << std::endl;
    int beggarDecider;
    std::cin >> beggarDecider;
    while ((beggarDecider != 0) || (beggarDecider != 1)) {
        if (beggarDecider == 0) {
            std::cout << "You did not give him anything." << std::endl;
            break;
        }
        else if (beggarDecider == 1) {
            std::cout << "Thank you good sir, may the god bless you." << std::endl;
            addRandomStat(p);
            break;
        }
        std::cout << "Invalid option!" << std::endl;
        std::cin >> beggarDecider;
    }
}

void events(character_stats* p) {
    int decider = randomizer(10);
    if (decider >= 8) {
        mysteriousMan(p);
    }
    else beggar(p);
}