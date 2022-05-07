#include <iostream>
#include "character.h"

const int shopListMax = 18;


struct item {
    std::string name;
    std::string type; // distinguish the item by using type variable (equipment/consumable)
    int atk, def, wis, vit, sta;
    int stock;
    int price;
};

item shopInventory[shopListMax] = {
        {"Iron Armor", "equipment", 0, 10, 0, 0, -5, 1, 100},
        {"Apprentice Robe", "equipment", 0, 5, 5, 0, 5, 1, 100},
        {"Iron Sword", "equipment", 10, 0, 0, 0, -1, 1, 100},
        {"Apprentice Staff", "equipment", 0, 0, 10, 0, 0, 1, 100},
        {"Steel Armor", "equipment", 0, 50, 0, 0, -8, 1, 1000},
        {"Regular Robe", "equipment", 0, 10, 35, 0, 5, 1, 1000},
        {"Steel Sword", "equipment", 50, 0, 0, 0, -3, 1, 1000},
        {"Regular Staff", "equipment", 0, 0, 50, 0, 0, 1, 1000},
        {"Adamant Armor", "equipment", 0, 80, 0, 0, -12, 1, 3000},
        {"Master Robe", "equipment", 0, 20, 60, 5, 5, 1, 3000},
        {"Adamant Sword", "equipment", 80, 0, 0, 0, -5, 1, 3000},
        {"Master Staff", "equipment", 0, 0, 80, 0, 0, 1, 3000},
        {"Rune Armor", "equipment", 0, 115, 0, 5, -18, 1, 6000},
        {"Mystic Robe", "equipment", 0, 40, 80, 10, 5, 1, 6000},
        {"Rune Sword", "equipment", 115, 0, 0, 0, -7, 1, 6000},
        {"Mystic Staff", "equipment", 0, 0, 115, 5, 0, 1, 6000},
        {"Health Potion (Restores 25% health)", "consumable", 0, 0, 0, 0, 0, 5, 250},
        {"Mage Potion (Restores 25% mp)", "consumable", 0, 0, 0, 0, 0, 5, 250}
};
//boss 300wis 300atk 200def 250sta 150vit
//max hp 5000
void printShopItems(item inv[]) {
    for (int i = 0; i < shopListMax; i++) {
        std::cout << "[" << i+1 << "] " << inv[i].name << ": $" << inv[i].price << " {";
        if (inv[i].atk != 0) {
            std::cout << "atk: " << inv[i].atk << ", ";
        }
        if (inv[i].def != 0) {
            std::cout << "def: " << inv[i].def << ", ";
        }
        if (inv[i].wis != 0) {
            std::cout << "wis: " << inv[i].wis << ", ";
        }
        if (inv[i].vit != 0) {
            std::cout << "vit: " << inv[i].vit << ", ";
        }
        if (inv[i].sta != 0) {
            std::cout << "sta: " << inv[i].sta << ", ";
        }
        std::cout << "stock: " << inv[i].stock << "}" << std::endl;
    }
}



int shop(character_stats *p) {
    int itemDecider = -999;
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Welcome to shop! Pick your item!" << std::endl;
    while (itemDecider != 0) {
        std::cout << "[0] Exit Shop" << std::endl;
        printShopItems(shopInventory);
        std::cout << "Which one would you Like? You currently have $" << p->money << "." << std::endl;
        std::cin >> itemDecider;
        if (itemDecider == 0) {
            std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top
            std::cout << "Come back next time!" << std::endl;
            break;
        }
        else if ((itemDecider > shopListMax) || (itemDecider < 0)) {
            std::cout << "Invalid Option!" << std::endl;
            std::cout << "Which one would you Like? You currently have $" << p->money << "." << std::endl;
            continue;
        }
        else if ((itemDecider != 0) && (shopInventory[itemDecider-1].stock != 0)) {
            p->money -= shopInventory[itemDecider-1].price;
            shopInventory[itemDecider-1].stock--;
            std::cout << "You have bought " << shopInventory[itemDecider-1].name << "!" << std::endl;
            p->change_inventory("add", -1, shopInventory[itemDecider-1].name);
        }
        else if (shopInventory[itemDecider-1].stock == 0) {
            std::cout << "It's out of stock!" << std::endl;
            std::cout << "Which one would you Like? You currently have $" << p->money << "." << std::endl;
            continue;
        };
    }
    return 0;
}