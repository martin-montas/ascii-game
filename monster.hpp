/*                   GNU GENERAL PUBLIC LICENSE
 *                      Version 3, 29 June 2007
 *
 *   Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
 *   Everyone is permitted to copy and distribute verbatim copies
 *   of this license document, but changing it is not allowed.
 *   
 *   This file is part of ascii-game.
 * 
 *   ascii-game is free software: you can redistribute it and/or 
 *   modify it under the terms of the GNU General Public License 
 *   as published by the Free Software Foundation, either 
 *   version 3 of the License, or (at your option) any later version.
 *   
 *   ascii-game is distributed in the hope that it will be useful, 
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *   See the GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License 
 *   along with ascii-game. 
 *   If not, see <https://www.gnu.org/licenses/>. 
 *  
 */
#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include <curses.h>
#include <unordered_map>
#include <utility>
#include <string>

#include "breadthFirstSearch.hpp"
#include "player.hpp"
#include "ncurses.hpp"

//class  Player;


struct Monster_data {
    char body;
    int color;
    int str;
    int life;
};

class Monster {
 protected:
        WINDOW *monster_window;
        int life;

        int power;
        int m_y, m_x;
        Player *player;
        char body;
        int color;
        std::string monster_name;
        std::unordered_map<std::string, Monster_data> data;
 public:
        // constructor here 
        Monster(WINDOW *win,Player *pl, std::string name,int power, char body,int color);
        void monster_generate_pos();
        void monster_update( int y, int x);
        int monster_attack();
        void monster_generate_drop();
        void monster_dies();
        void monster_data_def();
        bool monster_player_proximity();
        void monster_setter_pos(int y, int x) { m_y = y; m_x = x; }
        std::pair<int, int> monster_getter_pos() { return std::make_pair(m_y, m_x); }
        void monster_setter_life(int setter_health) { life = setter_health; }
        int monster_getter_life() { return life; }
};

#endif  // MONSTER_HPP_
