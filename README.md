# Realms and Might

A RPG text-based console game that involve player customization, gambling, and pve system.
Player can try out their luck and skills by fighting the ultimate boss.


## Game setting
- 30 in-game days for player to buy equipments/ level up/ train stats
- Player have to fight a strong boss after the 30 days.
- Each activities costs stamina. When stamina is used up, the game will proceed to the next day.
- Event will happen randomly that may help or negatively impact in-game progress
- Ranomly generated inital stats to add uniqueness.
- 3 difficulty level with different initial stats.
- Casino for players to test their luck

## Authors

- [@Wong Ying Kiu](https://github.com/yinkiu602)
- [@Yu Kai Man](https://github.com/ZinerX)


## Features

- [X]  Randomly generated initial stats
- [X]  Random events in mid-game
- [X]  Save and load game progress locally
- [X]  3 difficulty level
- [X]  Dynamic width for battle system message.

## Non standard library list
- #include <sys/ioctl.h> --> Used in battle_system.cpp to get the windows size to allow message width be dynamicly change depends on console width.

## Code Requirment
- [X]  Generation of random game sets or events                 --> Use of rand() to generate initial stats and events. (Feature 1&2)
- [X]  Data structures for storing game status                  --> Use of class/ struct to create and store user stats. (Feature 1&4)
- [X]  Dynamic memory management                                --> Use of vector to dynamically allocate memory.
- [X]  File input/output (e.g., for loading/saving game status) --> Use of fileio to save and reload game progress. (Feature 3&4)
- [X]  Program codes in multiple files
- [X]  Proper indentation and naming styles
- [X]  In-code documentation

## Installation environment

Compile the program with any C++ compiler (Parts of the code need to be changed when not compiling in linux)
(g++ in linux)

```bash
  make clean; make main
```
## Save-loading

Game progress will be saved in current working directory. No need to type the extension when loading / saving.
Sample save file provided with name "testsave"
