#include <iostream>

#include "blackjack.h"
#include "character.h"
#include "random.h"

// Predefined variable for blackjack
struct card {
    std::string name;
    int value;
};

const card cards[13] ={ // constant array that stores a deck of card
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

std::string playerCard[21] = {}; // stores player's hand of card
std::string houseCard[21] = {}; // stores house's hand of card
int playerSum = 0, houseSum = 0; // stores the sum of player's hand of card and house's hand

int hitStandDecider; // used to decide player's action
int blackjack_bet; // player's bet on the game
int randomint; // used to distribute card from the cards array
int playerCardCounter = 2, houseCardCounter = 2; // store card counts of both player and house
bool doubleDownAvailability = true; // used to check if the player can still double down or not

void clear_status() { // reset player's and house's status
    for (int i = 0; i < 21; i++) {
        playerCard[i] = "";
        houseCard[i] = "";
    }
    playerSum = 0;
    houseSum = 0;
    hitStandDecider = -1;
    blackjack_bet = -1;
    randomint = -1;
    playerCardCounter = 2;
    houseCardCounter = 2;
}

void printPlayerHand(std::string hand[]) { // print out player's hand of card when called
    std::cout << "Your hand: ";
    for (int i = 0; i <= playerCardCounter; i++) {
        std::cout << hand[i] << " ";
    }
    std::cout << std::endl;
}

void printHouseHand(std::string hand[]) { // print out house's hand of card when called
    std::cout << "House's hand: ";
    for (int i = 0; i <= houseCardCounter; i++) {
        std::cout << hand[i] << " ";
    }
    std::cout << std::endl;
}

void initializeGame() { // initialize the game by giving both the house and the player 2 cards
    for (int i = 0; i < 2; i++) {
        randomint = randomizer(13);
        houseCard[i] = cards[randomint].name;
        houseSum += cards[randomint].value;
        randomint = randomizer(13);
        playerCard[i] = cards[randomint].name;
        playerSum += cards[randomint].value;
    }
  doubleDownAvailability = true;
    std::cout << "House's hand: " << houseCard[0] << " " << houseCard[1] << std::endl;
    std::cout << "Your hand: " << playerCard[0] << " " << playerCard[1] << std::endl;
}

// decide how the house plays the game, the house will hit until it reaches 17 or more, then it will return true
// if the house busts during the function, it will return false to let the main function know
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
    if (houseSum <= 21) {
        return true;
    }
    else return false;
}


// main blackjack function
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
            std::cout << "Your blackjack_bet: ";
            std::cin >> blackjack_bet;
            if (blackjack_bet <= p->money) { break; }
            std::cout << "Insufficient money! Enter another amount!" << std::endl;
        }
        p->money -= blackjack_bet;
        initializeGame();
        while (hitStandDecider != 2) { // while loop for blackjack game, loop until player decides to stand, double down or busts
            if (playerSum > 21) {
              std::cout << "You busted!" << std::endl << "You have lost " << blackjack_bet << " credits" << std::endl;
              return 0;
            }
            if (doubleDownAvailability) { // if the player has already hit once, the player won't be able to double down.
              std::cout << "Hit(1)? Stand(2)? Or Double Down(3)?: ";
            }
            else std::cout << "Hit(1)? Stand(2)?: ";
            std::cin >> hitStandDecider;
            if (hitStandDecider == 1) { // hitting a card
                randomint = randomizer(13);
                playerCard[playerCardCounter] = cards[randomint].name;
                playerSum += cards[randomint].value;
                printPlayerHand(playerCard);
                playerCardCounter++;
                doubleDownAvailability = false;
            }

            else if ((hitStandDecider == 3) && (doubleDownAvailability)) { // doubling down and ending the loop
                p->money -= blackjack_bet;
                blackjack_bet *= 2;
                randomint = randomizer(13);
                playerCard[playerCardCounter] = cards[randomint].name;
                playerSum += cards[randomint].value;
                if (playerSum > 21) {
                  std::cout << "You busted!" << std::endl << "You have lost " << blackjack_bet << " credits" << std::endl;
                  return 0;
                }
                printPlayerHand(playerCard);
                playerCardCounter++;
                break;
            }
            else if (hitStandDecider == 2) break; // stand
            else std::cout << "Invalid Option!" << std::endl;
        }
        if (houseMove()) { // if house does not bust, it will proceed to this and see whose sum is higher to decide who wins
            if (playerSum > houseSum) {
                std::cout << "You win!" << std::endl << "You have won " << blackjack_bet << " credits" << std::endl;
                p->money += (blackjack_bet * 2);
            }
            else if (playerSum == houseSum) {
                std::cout << "It's a push!" << std::endl << "You win and lose nothing." << std::endl;
                p->money += blackjack_bet;
            }
            else if (houseSum > playerSum) {
                std::cout << "You lost!" << std::endl << "You have lost " << blackjack_bet << " credits" << std::endl;
            }
        }
        else {
            std::cout << "House busted!" << std::endl << "You have won " << blackjack_bet << " credits" << std::endl;
            p->money += (blackjack_bet * 2);
        }
        std::cout << "Game over! Do you want to start a new game? Type (1) to indicate Yes. (2) to indicate No." << std::endl;
        std::cin >> user_input;
        if (user_input == 2) { break; }
    }
    return 0;
}