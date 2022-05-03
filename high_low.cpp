#include <iostream>

#include "character.h"
#include "high_low.h"
#include "random.h"

struct card {
    std::string name;
    int value;
};

const card cards[13] =
{ 
    {"A", 1},
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
    {"10", 10},
    {"J", 11},
    {"Q", 12},
    {"K", 13}
};

card slotCard, pickedCard;
int hilo_bet;
int winnings;
int actionDecider = 0;

double calLowerPayout(card currentCard) {
    double totalLowerCardCount = 0;
    double probability;
    double payout;
    for (int i = 0; i < 13; i++) {
        if (cards[i].value < currentCard.value) {
            totalLowerCardCount++;
        }
    }
    if (totalLowerCardCount == 12) {
        return 0;
    }
    probability = totalLowerCardCount / 13;
    payout = 1 / probability;
    return payout;
}

double calHigherPayout(card currentCard) {
    double totalHigherCardCount = 0;
    double probability;
    double payout;
    for (int i = 0; i < 13; i++) {
        if (cards[i].value > currentCard.value) {
            totalHigherCardCount++;
        }
    }
    if (totalHigherCardCount == 12) {
        return 0;
    }
    probability = totalHigherCardCount / 13;
    payout = 1 / probability;
    return payout;
}


bool high_low(character_stats* p) {
    while (true) {
        std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top
        actionDecider = 0;
        std::cout << "Welcome to HILO!" << std::endl;
        int user_input = -1;
        std::cout << "1. Start a new game." << std::endl;
        std::cout << "2. Exit blackjack." << std::endl;
        std::cin >> user_input;
        if (user_input == 2) { break; }
        std::cout << "You currently have: " << p->money << std::endl;
        while (true) {
            std::cout << "Your hilo_bet: ";
            std::cin >> hilo_bet;
            if (hilo_bet <= p->money) { break; }
            std::cout << "Insufficient money! Enter another amount!" << std::endl;
        }
 
        slotCard = cards[randomizer(13)];
        std::cout << "Current Card: " << slotCard.name << std::endl;
        std::cout << "Is next card going to be lower(1) (Payout: " << calLowerPayout(slotCard) << ") or higher(2) (Payout: " << calHigherPayout(slotCard) << ") ? Or you are going to call it quits(3)?";

        std::cin >> actionDecider;
        while (actionDecider != 3) {
            pickedCard = cards[randomizer(13)];
            std::cout << "Next Card: " << pickedCard.name << std::endl;
            if ((pickedCard.value < slotCard.value) && (actionDecider == 1)) {
                winnings += hilo_bet * calLowerPayout(slotCard);
                std::cout << "You are right!, Your current winnings: " << winnings << std::endl;
            }
            else if ((pickedCard.value < slotCard.value) && (actionDecider == 2)) {
                winnings -= hilo_bet;
                std::cout << "You are wrong!, Your current winnings: " << winnings << std::endl;
            }
            else if ((pickedCard.value > slotCard.value) && (actionDecider == 2)) {
                winnings += hilo_bet * calHigherPayout(slotCard);
                std::cout << "You are right!, Your current winnings: " << winnings << std::endl;
            }
            else if ((pickedCard.value > slotCard.value) && (actionDecider == 1)) {
                winnings -= hilo_bet;
                std::cout << "You are right!, Your current winnings: " << winnings << std::endl;
            }
            slotCard = pickedCard;
            std::cout << "Current Card: " << slotCard.name << std::endl;
            std::cout << "Is next card going to be lower(1) (Payout: " << calLowerPayout(slotCard) << ") or higher(2) (Payout: " << calHigherPayout(slotCard) << ") ? Or you are going to call it quits(3)?";
            std::cin >> actionDecider;
        }
        p->money += winnings;
        std::cout << "Game over! " << "You currently have: " << p->money << std::endl;
        std::cout << "Want to start a new game? Type (1) to indicate Yes. (2) to indicate No." << std::endl;
        std::cin >> user_input;
        if (user_input == 2) { break; }
    }
    return 0;
}