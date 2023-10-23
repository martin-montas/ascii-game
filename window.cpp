// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#include <curses.h>
#include <ncurses.h>

#include "window.hpp"
#include "ncurses.hpp"


WINDOW *Window::Init(int y, int x) {
    WINDOW *win = newwin(LINES,  COLS, y, x);
    keypad(win, true);
    refresh();
    wrefresh(win);
    refresh();
    wrefresh(win);
    keypad(win, true);
    Ncurses::update_window(win);

    return win;
}
