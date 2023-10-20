// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#include "ncurses.hpp"
#include "game.hpp"
#include <curses.h>

int main() {

    initscr(); // initiates ncurses
    cbreak();  // c-style breaks
    noecho();  // dont' echo key presses
    curs_set(0);
    start_color();// initiates colors

    Game *g = new Game();
    //Ncurses::init_screen();
    g->Run();
    endwin();
    delete g;
    
}
