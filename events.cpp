#include <iostream>
#include <random>
#include "character.h"
#include "random.h"
#include "battle_system.h"

std::random_device randomiser; // randomizer for legendary items
std::mt19937 generator(randomiser());
std::uniform_int_distribution<> range(0, 3);

struct item {
    std::string name;
    std::string type; // distinguish the item by using type variable (equipment/consumable)
    int atk, def, wis, vit, sta;
    int stock;
    int price;
};

item legendaryItem[4] {  // stores the legendary items sold by the mysterious merchant
    {"Kodai Wand", "equipment", 0, 0, 175, 15, 0, 1, 10000},
    {"Ancestral Robe", "equipment", 0, 75, 150, 15, 5, 1, 10000},
    {"Ghrazi Rapier", "equipment", 200, 0, 0, 10, 5, 1, 10000},
    {"Justiciar Armor", "equipment", 0, 250, 0, 5, -20, 1, 10000},
};

void bloodMoon(character_stats* p) { // bloodmoon event that forces player into a series of fight
    int enemiesCount = randomizer(5); // random enemies count
    std::cout << "As you walk down the streets, the sky turns into a dark red color." << std::endl;
    std::cout << "You hear growls near you, looks like you are in deep trouble as bloodmoon crawls in..." << std::endl;
    for (int i = 0; i < enemiesCount; i++) { // for loop to give players fights
        battle_system(p, "small");
    }
    std::cout << "This one looks stronger than the others, this is probably the final of them." << std::endl;
    battle_system(p, "big"); // last fight must be a stronger variant of enemy
    std::cout << "You survived this bloodmoon, but you know that they will come back stronger..." << std::endl;
}

void mysteriousMan(character_stats* p) { // mysterious merchant event that gives you a chance to buy 1 of the 4 legendary items
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
    int itemDecider; // stores decision of player
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

void addRandomStat(character_stats* p) { // function to increase a random
    std::string statname[5] = { "ATK", "DEF", "WIS", "STA", "VIT" };
    int statadddecider = randomizer(5);
    p->change_stat(statname[statadddecider], 5);
    std::cout << "You felt a warm pulse inside you, you think you have understood something. (" << statname[statadddecider] << " increased)" << std::endl;
}

void beggar(character_stats* p) { // beggar event where if player decides to give money to the beggar, he will be blessed by the lord and get stat points
    std::cout << "As you walked down the road, you see a beggar begging for money..." << std::endl;
    std::cout << "Goodday sir, would you mind sparing me a few clangs?" << std::endl;
    std::cout << "[0] Quit" << std::endl << "[1] Give him $100" << std::endl;
    int beggarDecider; // stores the decision of player
    std::cin >> beggarDecider;
    while ((beggarDecider != 0) || (beggarDecider != 1)) { // player deciding whether or not to give the beggar money
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

void events(character_stats* p) { //main function of random events, randomly generate a number and goes into different events according to the condition
    int decider = randomizer(11);
    if (decider == 10) {
        bloodMoon(p);
    }
    else if (decider >= 9) {
        mysteriousMan(p);
    }
    else beggar(p);
}