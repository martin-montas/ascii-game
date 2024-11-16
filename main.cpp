// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#include <curses.h>

#include "ncurses.hpp"
#include "game.hpp"
int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    Game *g = new Game();
    Ncurses::init_screen();
    g->Run();
    endwin();
    delete g;
}
