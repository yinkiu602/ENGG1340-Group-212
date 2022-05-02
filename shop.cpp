#include <iostream>
#include "character.h"

const int shopListMax = 5;
int itemDecider = -999;

struct item {
    std::string name;
    std::string type; // distinguish the item by using type variable (equipment/consumable)
    int atk, def, wis, vit, sta;
    int stock;
    int price;
    int id;
};

item shopInventory[shopListMax] = {
        {"Iron Armor", "equipment", 0, 10, 0, 0, -5, 1, 100, 1},
        {"Apprentice Robe", "equipment", 0, 0, 5, 0, 5, 1, 100, 2},
        {"Iron Sword", "equipment", 10, 0, 0, 0, -1, 1, 100, 3},
        {"Apprentice Staff", "equipment", 0, 0, 10, 0, 0, 1, 100, 4}
};

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
    std::cout << "Welcome to shop! Pick your item!" << std::endl;
    std::cout << "[0] Exit Shop" << std::endl;
    printShopItems(shopInventory);
    std::cout << "Which one would you Like? You currently have $" << p->money << "." << std::endl;
    while (itemDecider != 0) {
        std::cin >> itemDecider;
        if (itemDecider == 0) {
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
        printShopItems(shopInventory);
        std::cout << "Which one would you Like? You currently have $" << p->money << "." << std::endl;
    }
    return 0;
}