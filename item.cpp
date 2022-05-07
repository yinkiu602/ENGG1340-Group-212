#include <iostream>
#include <map>

#include "character.h"

// Stats struct for storing the values of items
struct stats {
    int atk, def, wis, vit, sta;
};

// Map to convert item name to stats
std::map<std::string, stats> converter{
    { "Iron Armor"      , {0, 10, 0, 0, -5}},
    { "Apprentice Robe" , {0, 0, 5, 0, 5 }},
    { "Iron Sword"      , {10, 0, 0, 0, -1}},
    { "Apprentice Staff", {0, 0, 10, 0, 0 }},
    { "Steel Armor"     , {0, 50, 0, 0, -8}},
    { "Regular Robe"    , {0, 10, 35, 0, 5 }},
    { "Steel Sword"     , {50, 0, 0, 0, -3}},
    { "Regular Staff"   , {0, 0, 50, 0, 0 }},
    { "Adamant Armor"   , {0, 80, 0, 0, -12}},
    { "Master Robe"     , {0, 20, 60, 5, 5 }},
    { "Adamant Sword"   , {80, 0, 0, 0, -5}},
    { "Master Staff"    , {0, 0, 80, 0, 0 }},
    { "Rune Armor"      , {0, 115, 0, 5, -18}},
    { "Mystic Robe"     , {0, 40, 80, 10, 5 }},
    { "Rune Sword"      , {115, 0, 0, 0, -7}},
    { "Mystic Staff"    , {0, 0, 115, 5, 0}},
    { "Justiciar Armor" , {0, 200, 0, 10, -15}},
    { "Ancestral Robe"  , {0, 75, 150, 15, 5}},
    { "Ghrazi Rapier"   , {175, 0, 0, 10, 5}},
    { "Kodai Wand"      , {0, 0, 175, 15, 0}}
};

bool equip(character_stats* p, std::string action, std::string equip_name, int item_index) {
    if (action == "equip") {
        if (p->search_inventory(equip_name)) { // If exist in inventory. (Although checking not necessary)

            // HP / MP potion no need equip. Consume and remove from inventory directly.
            if (equip_name == "Health Potion (Restores 25% health)") {
                p->change_inventory("remove", item_index - 1, "");
                p->change_stat("HP", (int)(p->read_specific_stat("HP_MAX") * 0.25));
            }
            else if (equip_name == "Mage Potion (Restores 25% mp)") {
                p->change_inventory("remove", item_index - 1, "");
                p->change_stat("MP", (int)(p->read_specific_stat("MP_MAX") * 0.25));
            }

            if (!(p->search_equipped(equip_name))) { // If not equipeed
                p->change_equipeed("equip", equip_name); // Equip the item, add to equipped vector
                p->change_stat("ATK", converter[equip_name].atk);
                p->change_stat("DEF", converter[equip_name].def);
                p->change_stat("WIS", converter[equip_name].wis);
                p->change_stat("VIT", converter[equip_name].vit);
                p->change_stat("STA", converter[equip_name].wis);
                return true;
            }
        }
        return false;
    }
    else {
        // Unequip
        if (p->search_equipped(equip_name)) {
            p->change_equipeed("", equip_name); // Remove the item from equipped vector
            p->change_stat("ATK", -converter[equip_name].atk);
            p->change_stat("DEF", -converter[equip_name].def);
            p->change_stat("WIS", -converter[equip_name].wis);
            p->change_stat("VIT", -converter[equip_name].vit);
            p->change_stat("STA", -converter[equip_name].wis);
            return true;
        }
        else {
            return false;
        }
    }
}
