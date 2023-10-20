// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <ncurses.h>
#include <string>
#include <vector>

#define GREEN_COL 1
#define BLUE_COL 2
#define RED_COL 4
#define MAGENTA_COL 5
#define YELLOW_COL 3
#define DEAD_COL  6
#define HIGH_LIGHT 7
namespace Ncurses {
    void init_colors();
    void exit();
    void draw_map(std::string path, WINDOW *win);
    void update_life_point(WINDOW *win, int val);
    void update_strength_point(WINDOW *win, int val);
    void update_window(WINDOW *win);
    void update_Level(WINDOW *win, int val);
    void init_screen();
    void del_win(WINDOW *win);
    void end_event();
    void set_alert_win(WINDOW *win);
    WINDOW *exit_win(WINDOW *win);
    void player_sees(WINDOW *win, char body, int color,std::string name);
    void set_player_sees(WINDOW *win);
    void set_window_command(WINDOW *win);
    extern int pressed_key;

}; // namespace Ncurses
#endif  // NCURSES_HPP_
