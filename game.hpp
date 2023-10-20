// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#ifndef GAME_HPP_
#define GAME_HPP_

#include <curses.h>
#include <ncurses.h>
#include <panel.h>
#include <vector>

#include "window.hpp"
#include "player.hpp"
#include "monster.hpp"

enum quit_status {
 QUIT_NO = 0,  // Still playing
 QUIT_MENU,    // Quit at the menu
 QUIT_DIED     // Actual death
};
class Game {
 public:
    Game();
    ~Game();
    //void init_dungeon();

    void Run();
    void generate_monster(WINDOW *win, int amount,std::string name);
    void game_alert_resize();
    void handle_exit_win(int in);
    void level00();


 private:

    Player *player;
    Window  win;

    bool    game_over; 

    WINDOW *m_win; // main window
    WINDOW *ext_win;

    PANEL  *ext_panel;
    PANEL  *alrt_panel;
    PANEL  *m_panel;

    // the following vector is used to 
    // deallocate the monsters
    std::vector<Monster *> monsters;

    quit_status uquit;
};

#endif  // GAME_HPP_
