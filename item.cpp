#include <iostream>
#include <map>

#include "character.h"

struct stats {
    int atk, def, wis, vit, sta;
};

stats test = { 1,1,1,1,1 };
std::map<std::string, stats> converter{
    { "Iron Armor"      , {0, 10, 0, 0, -5}},
    { "Apprentice Robe" , {0, 0, 5, 0, 5 }},
    { "Iron Sword"      , {10, 0, 0, 0, -1}},
    { "Apprentice Staff", {0, 0, 10, 0, 0 }},
    { "Steel Armor"     , {0, 10, 0, 0, -5}},
    { "Regular Robe"    , {0, 0, 5, 0, 5 }},
    { "Steel Sword"     , {10, 0, 0, 0, -1}},
    { "Regular Staff"   , {0, 0, 10, 0, 0 }},
    { "Adamant Armor"   , {0, 10, 0, 0, -5}},
    { "Master Robe"     , {0, 0, 5, 0, 5 }},
    { "Adamant Sword"   , {10, 0, 0, 0, -1}},
    { "Master Staff"    , {0, 0, 10, 0, 0 }},
    { "Rune Armor"      , {0, 10, 0, 0, -5}},
    { "Mystic Robe"     , {0, 0, 5, 0, 5 }},
    { "Rune Sword"      , {10, 0, 0, 0, -1}},
    { "Mystic Staff"    , {0, 0, 10, 0, 0 }}
};

bool equip(character_stats* p, std::string action, std::string equip_name) {
    if (action == "equip") {
        if (p->search_inventory(equip_name)) { // If exist in inventory. (Although checking not necessary)
            if (!(p->search_equipped(equip_name))) { // If not equipeed
                p->change_equipeed("equip", equip_name);
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
        if (p->search_equipped(equip_name)) {
            p->change_equipeed("", equip_name);
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
