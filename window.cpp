// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#include <curses.h>

#include "window.hpp"
#include "ncurses.hpp"


WINDOW *Window::Init(int y, int x) {
    win = newwin(LINES,  COLS, y, x);
    keypad(win, true);
    refresh();
    wrefresh(win);
    refresh();
    wrefresh(win);
    keypad(win, true);
    Ncurses::update_window(win);

    return win;
}
void Window::set_player_sees() {
    mvwprintw(win, 10, 80, "Player sees:");
    wrefresh(win);
}

void Window::update_strength_point(int val) {
    mvwprintw(win, 4, 80, "ATK: %d", val);
    wrefresh(win);
}

void Window::set_window_command() {
    /* todo better logic for when there is resizing */

    wattrset(win, A_NORMAL | COLOR_PAIR(RED_COL)); 
    mvwaddch(win, LINES -30, 1, 'Q'); 
    wrefresh(win);

    wattrset(win, A_NORMAL); 
    mvwprintw(win,LINES - 30, 2, "uit");
    wrefresh(win);


}
