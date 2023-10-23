// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <ncurses.h>
#include <algorithm>
#include <utility>
#include <vector>
#include "player.hpp"

enum Player_status {
    STATUS_DIED,   // the player was killed
    STATUS_ALIVE,  // the player is still alive
};

class  Monster;

class  Player {
 public:
        Player(WINDOW* win);
        void PlayerMove(int in);
        void PlayerUpdate(WINDOW *win, int in);
        void PlayerLifeUpdate(int amount);
        bool PLayerWithinProximity(std::pair<int, int> enemy_pos);
        bool PlayerCanBeMove(WINDOW *win,int in);
        void player_attack (WINDOW *win);
        void PlayerHealthSetter(int set_health) {
            this->player_life = set_health;
        }int PlayerHealthGetter() {
            return player_life;
        }
        void PlayerPosSetter(int y, int x) {
            this->ypos = y;
            this->xpos = x;
        }
        std::pair<int, int> PlayerPosGetter() {
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
