# Realms and Might

A RPG text-based console game


## Game setting
- 30 in-game days for player to buy equipments/ level up/ train stats
- Player have to fight a strong boss after the 30 days.
- Each activities costs stamina. When stamina is used up, the game will proceed to the next day.
- Event will happen randomly that may help or negatively impact in-game progress
- Ranomly generated inital stats to add uniqueness.
- 3 difficulty level with different initial stats.
- Auto save after the completition of one in-game day.

## Authors

- [@Wong Ying Kiu](https://github.com/yinkiu602)
- [@Yu Kai Man](https://github.com/ZinerX)


## Features

- [ ]  Randomly generated initial stats
- [ ]  Random events in mid-game
- [ ]  Save and load game progress locally
- [ ]  Locally saved scoreboard
- [ ]  3 difficulty level



## Code Requirment
- [ ]  Generation of random game sets or events                 --> Use of rand() to generate initial stats and events. (Feature 1&2)
- [ ]  Data structures for storing game status                  --> Use of struct to create and store user stats. (Feature 1&4)
- [ ]  Dynamic memory management                                --> Use of pointer to dynamicly allocate memory. (Example: Dynamic sized array for inventory tracking. Array deletion when random event is finished. delete[])
- [ ]  File input/output (e.g., for loading/saving game status) --> Use of fileio to save and reload game progress and scoreboard. (Feature 3&4)
- [ ]  Program codes in multiple files
- [ ]  Proper indentation and naming styles
- [ ]  In-code documentation

## Installation environment (TODO) 

Compile the program with any C++ compiler
(g++ in linux / Mingw-w64 in Windows)

```bash
  make ( Utilize the makefile. TODO )
  g++ -pedantic-errors -std=c++11
```
