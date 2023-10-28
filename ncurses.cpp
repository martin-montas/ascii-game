// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include "ncurses.hpp"

void Ncurses::init_colors() {
    init_pair(GREEN_COL, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLUE_COL , COLOR_BLUE, COLOR_BLACK);
    init_pair(RED_COL, COLOR_RED, COLOR_BLACK);
    init_pair(MAGENTA_COL, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(YELLOW_COL, COLOR_YELLOW, COLOR_BLACK);
    init_pair(DEAD_COL, COLOR_YELLOW, COLOR_RED);
    init_pair(HIGH_LIGHT, COLOR_BLACK, COLOR_WHITE);
    refresh();
    clear();
}

void Ncurses::exit() {
    endwin();
}

void Ncurses::update_Level(WINDOW *win, int val) {
    mvwprintw(win, 1, 80, "Dungeon Lvl: %d ", val);
    Ncurses::update_window(win);
}

void Ncurses::player_sees(WINDOW *win, char body, int color,std::string name) {
    wattrset(win, A_NORMAL | COLOR_PAIR(color)); 
    mvwaddch(win, 11, 80, body); 
    Ncurses::update_window(win);

    /* sets the new attribute */
    wattrset(win, A_NORMAL); 
    mvwprintw(win, 11, 82, "%s", name.c_str());
    Ncurses::update_window(win);

}

void Ncurses::update_life_point(WINDOW *win,int val) {
    mvwprintw(win, 3, 80, "HP:%d", val);
    wrefresh(win);
}

void Ncurses::update_window(WINDOW *win) {
    wrefresh(win);
    refresh();
}

void Ncurses::init_screen() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    WINDOW *logo_win = newwin(max_y/2, max_x/2, (max_y/4) -10 , max_x/4);
    Ncurses::update_window(logo_win);
    wattron(logo_win, COLOR_PAIR(MAGENTA_COL));
    Ncurses::draw_map("./map/initScreen.txt", logo_win);
    wattroff(logo_win, COLOR_PAIR(MAGENTA_COL));
    Ncurses::update_window(logo_win);
    wattron(stdscr, COLOR_PAIR(GREEN_COL));
    mvwprintw(stdscr, (max_y/4) +24, (max_x/4) + 35, "Version 0.0.1");
    wattroff(stdscr, COLOR_PAIR(GREEN_COL));
    Ncurses::update_window(stdscr);
    WINDOW *menu_win = newwin(10, 24, (max_y/4) +10, (max_x/4) +30);
    box(menu_win, 0, 0);
    wattron(menu_win, COLOR_PAIR(YELLOW_COL));
    mvwprintw(menu_win, 1, 4, "PRESS S TO START");
    wattroff(menu_win, COLOR_PAIR(YELLOW_COL));
    wattron(menu_win, COLOR_PAIR(RED_COL));
    mvwprintw(menu_win, 3, 4, "PRESS Q TO QUIT");
    wattroff(menu_win, COLOR_PAIR(RED_COL));
    Ncurses::update_window(menu_win);

    /*
       int c;
       switch((c = wgetch(stdscr))) {
       case 'S':
       case 's':
       break;

       case 'q':
       case 'Q':
       break;
       }
       */
}

/*
 *
 */



WINDOW *Ncurses::exit_win(WINDOW *win) {
    int max_y, max_x,sub_max_y,sub_max_x, _y, _x;

    getmaxyx(stdscr, max_y, max_x);
    WINDOW *exit_win = newwin(LINES/4, COLS/4, LINES/4, COLS/4);
    refresh();
    box(exit_win, 0, 0);
    getmaxyx(exit_win,sub_max_y,sub_max_x);
    Ncurses::update_window(exit_win);
    std::string message = "Exit?";
    std::string cont = "(n)Continue";
    std::string exit = "(y)Exit";
    getmaxyx(exit_win, _y, _x);

    // sets the message to exit
    wattron(exit_win, COLOR_PAIR(RED_COL));
    getmaxyx(exit_win, max_y, max_x);
    mvwprintw(exit_win, max_y/4, max_x/4, message.c_str());
    wattroff(exit_win, COLOR_PAIR(RED_COL));
    Ncurses::update_window(exit_win);

    // should it continue
    wattron(exit_win, COLOR_PAIR(HIGH_LIGHT));
    mvwprintw(exit_win, max_y/4+2, max_x/4, cont.c_str());
    wattroff(exit_win, COLOR_PAIR(HIGH_LIGHT));
    Ncurses::update_window(exit_win);

    // should it exit
    wattron(exit_win, COLOR_PAIR(HIGH_LIGHT));
    mvwprintw(exit_win, max_y/4+3, max_x/4, exit.c_str());
    wattroff(exit_win, COLOR_PAIR(HIGH_LIGHT));
    Ncurses::update_window(exit_win);

    return exit_win;
}

void Ncurses::del_win(WINDOW *win) {
    delwin(win);
}

void Ncurses::set_alert_win(WINDOW *win) {
    box(win,0,0);
    mvwprintw(win, 0, 0, "this is a test for debug");
}

void Ncurses::draw_map(std::string path, WINDOW *win) {
    int height, width;
    getmaxyx(win, height, width);
    std::ifstream file(path);
    std::string str;
    int row = 0;
    int index = 0;
    while (std::getline(file, str)) {
        mvwprintw(win, row, 0, "%s", str.c_str());
        Ncurses::update_window(win);
        row++;
        if (row == height)  {
            break;
        }
    }
}


