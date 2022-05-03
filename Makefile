FLAGS = -pedantic-errors -std=c++11


#structure.o: structure.h
#	g++ -pedantic-errors -std=c++11 -c structure.o
events.o: events.cpp events.h character.h random.h
	g++ $(FLAGS) -c $<
random.o: random.cpp random.h
	g++ $(FLAGS) -c $<
character.o: character.cpp character.h
	g++ $(FLAGS) -c $<
saveload.o: saveload.cpp saveload.h character.h
	g++ $(FLAGS) -c $<
training.o: training.cpp training.h character.h random.h
	g++ $(FLAGS) -c $<
battle_system.o: battle_system.cpp battle_system.h character.h
	g++ $(FLAGS) -c $<
shop.o: shop.cpp shop.h character.h
	g++ $(FLAGS) -c $<
item.o: item.cpp item.h
	g++ $(FLAGS) -c $<
blackjack.o: blackjack.cpp blackjack.h character.h random.h
	g++ $(FLAGS) -c $<
high_low.o: high_low.cpp high_low.h character.h random.h
	g++ $(FLAGS) -c $<
casino.o: casino.cpp casino.h high_low.h blackjack.h character.h
	g++ $(FLAGS) -c $<
progress.o: progress.cpp progress.h character.h training.h events.h random.h
	g++ $(FLAGS) -c $<
main.o: main.cpp character.h saveload.h progress.h
	g++ $(FLAGS) -c $<
main: main.o random.o character.o saveload.o training.o battle_system.o shop.o item.o blackjack.o high_low.o casino.o progress.o events.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm *.o main
cleansave:
	rm *.gamesave

.PHONY: clean cleansave

