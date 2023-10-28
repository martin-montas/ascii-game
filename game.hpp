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
 STATUS_PLAYING = 0, // Still playing
 STATUS_PAUSED,     // pauses the game(no keystrokes on the current window)
 STATUS_QUIT,      // Actual death
 STATUS_MENU,      // menu was invoked
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
    void generate_monster_group();


 private:
    Player *player;
    Window  window;

    bool    game_over; 

    std::unordered_map<int, Monster *> mon_group;
    WINDOW *m_win; 
    WINDOW *ext_win;

    PANEL  *ext_panel;
    PANEL  *alrt_panel;
    PANEL  *m_panel;
    bool change_map;
    // the following vector is used to 
    // deallocate the monsters
    std::vector<Monster *> monsters;
    std::vector<unsigned int> monster_killed;
    quit_status ustatus;
    Monster *mon;

};
#endif  // GAME_HPP_
