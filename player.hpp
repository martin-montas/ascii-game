/*                   GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
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
        //int PlayerAttack(WINDOW *win, std::pair<int, int> enemy_pos, int enemy_health, char monster_body);
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
        void notify_monsters_moved();
        void notify_monsters_attack();
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
