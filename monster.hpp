// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include <curses.h>
#include <unordered_map>
#include <utility>
#include <string>

#include "breadthFirstSearch.hpp"
#include "player.hpp"
#include "ncurses.hpp"

//class Player;


struct Monster_data {
    char body;
    int color;
    int str;
    int life;
};

class Monster {
 protected:
        WINDOW *win;
        int life;
        int _id;

        int power;
        int m_y, m_x;
        Player *player;
        char body;
        int color;
        std::string monster_name;
        std::unordered_map<std::string, Monster_data> data;
 public:
        bool is_dead;
        // constructor here 
        Monster(int _id, WINDOW *win,Player *pl, std::string name,int power, char body,int color);
        void monster_generate_pos();
        void monster_update( int y, int x);
        int monster_attack();
        void monster_generate_drop();
        void monster_dies();
        void monster_data_def();
        bool monster_player_proximity();
        void monster_setter_pos(int y, int x) { m_y = y; m_x = x; }
        std::pair<int, int> monster_getter_pos() { return std::make_pair(m_y, m_x); }
        void monster_setter_life(int setter_health) { life = setter_health; if (life == 0) { monster_dies(); } }
        int monster_getter_life() { return life; }
};

#endif  // MONSTER_HPP_
