CC = g++
CFLAGS = --std=c++14  -fsanitize=address -g -pg -Og -w
LIB = -l ncurses -l panel

all: 	game

game:   main.o  ncurses.o  game.o   window.o  player.o monster.o    breadthFirstSearch.o

	$(CC) $(CFLAGS) main.o ncurses.o game.o window.o  player.o  monster.o -o game breadthFirstSearch.o $(LIB)

main.o: main.cpp

	$(CC) $(CFLAGS) -c main.cpp

ncurses.o:   ncurses.cpp 	ncurses.hpp

	$(CC) $(CFLAGS) -c ncurses.cpp

game.o:   game.cpp 	game.hpp

	$(CC) $(CFLAGS) -c game.cpp

window.o:   window.cpp 	window.hpp

	$(CC) $(CFLAGS) -c window.cpp

player.o:   player.cpp player.hpp

	$(CC) $(CFLAGS) -c player.cpp

monster.o:   monster.cpp monster.hpp

	$(CC) $(CFLAGS) -c monster.cpp


breadthFirstSearch.o:   breadthFirstSearch.cpp breadthFirstSearch.hpp

	$(CC) $(CFLAGS) -c breadthFirstSearch.cpp

lint:

	cpplint --filter=-runtime/references,-build/c++11,-build/include_subdir --root=. *
	
clean:

	rm *.o game
