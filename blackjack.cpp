#include <iostream>

#include "blackjack.h"
#include "character.h"
#include "random.h"

// Predefined variable for blackjack
struct card {
    std::string name;
    int value;
};

const card cards[13] ={
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
    {"J", 10},
    {"Q", 10},
    {"K", 10}
};

std::string playerCard[21] = {};
std::string houseCard[21] = {};
int playerSum = 0, houseSum = 0;

int hitStandDecider;
int bet;
int randomint;
int playerCardCounter = 2, houseCardCounter = 2;

void clear_status() {
    for (int i = 0; i < 21; i++) {
        playerCard[i] = "";
        houseCard[i] = "";
    }
    playerSum = 0;
    houseSum = 0;
    hitStandDecider = -1;
    bet = -1;
    randomint = -1;
    playerCardCounter = 2;
    houseCardCounter = 2;
}

void printPlayerHand(std::string hand[]) {
    std::cout << "Your hand: ";
    for (int i = 0; i <= playerCardCounter; i++) {
        std::cout << hand[i] << " ";
    }
    std::cout << std::endl;
}

void printHouseHand(std::string hand[]) {
    std::cout << "House's hand: ";
    for (int i = 0; i <= houseCardCounter; i++) {
        std::cout << hand[i] << " ";
    }
    std::cout << std::endl;
}

void initializeGame() {
    for (int i = 0; i < 2; i++) {
        randomint = randomizer(13);
        houseCard[i] = cards[randomint].name;
        houseSum += cards[randomint].value;
        randomint = randomizer(13);
        playerCard[i] = cards[randomint].name;
        playerSum += cards[randomint].value;
    }
    std::cout << "House's hand: " << houseCard[0] << " " << houseCard[1] << std::endl;
    std::cout << "Your hand: " << playerCard[0] << " " << playerCard[1] << std::endl;
    std::cout << "Hit(1)? Stand(2)? Or Double Down(3)?: ";
}

bool houseMove() {
    while (houseSum < 17) {
        if (houseSum > 21) {
            printHouseHand(houseCard);
            return false;
        }
        randomint = randomizer(13);
        houseCard[houseCardCounter] = cards[randomint].name;
        houseSum += cards[randomint].value;
        printHouseHand(houseCard);
        houseCardCounter++;
    }
    if (houseSum < 21) {
        return true;
    }
    else return false;
}

bool blackjack(character_stats* p) {
    while (true) {
        std::cout << "\033[2J\033[1;1H"; // Clear the screen and allow the lines to be printed on top
        clear_status();
        std::cout << "BLACKJACK" << std::endl << "-----------------------" << std::endl;
        int user_input = -1;
        std::cout << "1. Start a new game." << std::endl;
        std::cout << "2. Exit blackjack." << std::endl;
        std::cin >> user_input;
        if (user_input == 2) { break; }
        std::cout << "You currently have: " << p->money << std::endl;
        while (true) {
            std::cout << "Your bet: ";
            std::cin >> bet;
            if (bet <= p->money) { break; }
            std::cout << "Insufficient money! Enter another amount!" << std::endl;
        }
        p->money -= bet;
        initializeGame();
        std::cin >> hitStandDecider;
        while (hitStandDecider != 2) {

            if (playerSum > 21) {
                std::cout << "You busted!" << std::endl << "You have lost " << bet << " credits" << std::endl;
                return 0;
            }

            if (hitStandDecider == 1) {
                randomint = randomizer(13);
                playerCard[playerCardCounter] = cards[randomint].name;
                playerSum += cards[randomint].value;
                printPlayerHand(playerCard);
                playerCardCounter++;
            }

            if (hitStandDecider == 3) {
                p->money -= bet;
                bet *= 2;
                randomint = randomizer(13);
                playerCard[playerCardCounter] = cards[randomint].name;
                playerSum += cards[randomint].value;
                printPlayerHand(playerCard);
                playerCardCounter++;
                break;
            }
            std::cout << "Hit(1)? Stand(2)? Or Double Down(3)?: ";
            std::cin >> hitStandDecider;
        }
        if (houseMove()) {
            if (playerSum > houseSum) {
                std::cout << "You win!" << std::endl << "You have won " << bet << " credits" << std::endl;
                p->money += (bet * 2);
            }
            else if (playerSum == houseSum) {
                std::cout << "It's a push!" << std::endl << "You win and lose nothing." << std::endl;
                p->money += bet;
            }
            else if (houseSum > playerSum) {
                std::cout << "You lost!" << std::endl << "You have lost " << bet << " credits" << std::endl;
            }
        }
        else {
            std::cout << "House busted!" << std::endl << "You have won " << bet << " credits" << std::endl;
            p->money += (bet * 2);
        }
        std::cout << "Game over! Do you want to start a new game? Type (1) to indicate Yes. (2) to indicate No." << std::endl;
        std::cin >> user_input;
        if (user_input == 2) { break; }
    }
    return 0;
}