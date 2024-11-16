// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <ncurses.h>
#include <utility>
#include <vector>

// #include "player.hpp"

enum Player_status {
    STATUS_DIED,   // the player was killed
    STATUS_ALIVE,  // the player is still alive
};

class  Monster;

class  Player {
 public:
        explicit Player(WINDOW* win);
        void player_move(int in);
        void generate_player_pos();
        void player_update(int in);
        void player_life_update(int amount);
        bool player_proximity(std::pair<int, int> enemy_pos);
        bool player_can_move(int in);
        void player_attack();
        bool notify_all_monster_life();
        void setter_player_health(int set_health) {
            this->player_life = set_health;
        }int getter_player_health() {
            return player_life;
        }
        void setter_player_pos(int y, int x) {
            this->ypos = y;
            this->xpos = x;
        }
        std::pair<int, int> getter_player_pos() {
            return std::make_pair(ypos, xpos);
        }
        bool get_moved_state();
        void set_moved_state(bool new_state);
        void attach(Monster *mon);
        void detach(Monster *mon);
        void notify_monsters_move();
        void notify_monster_hit();

 private:
        std::vector<Monster *> monsters;
        int ypos, xpos;
        WINDOW *win;
        bool state;
        int player_strength;
        int player_life;
        bool is_alive;
        Player_status pstatus;
};
#endif  // PLAYER_HPP_
