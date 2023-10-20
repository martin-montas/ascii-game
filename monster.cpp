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
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <unordered_map>

#include "monster.hpp"
#include "ncurses.hpp"
#include "window.hpp"
#include "breadthFirstSearch.hpp"

std::vector<int> life_drop  = {10, 15, 30};
std::vector<int> armor_drop = {8, 10, 5};
int random_loot, random_index, drop;


Monster::Monster( WINDOW *win,Player *pl, std::string name,int power, char body,int color) {

    this->player = pl;
    this->monster_name = name;
    this->power = power;
    this->color = color;
    this->body = body;
    life = 13;
    monster_name = name;
    monster_window = win;
    monster_generate_pos();
    Ncurses::player_sees(monster_window, body, color, monster_name);
    Ncurses::update_window(monster_window);
}

void Monster::monster_update(int p_y, int p_x) {
    if ( life >0) {
        Node  end = std::make_pair(p_y, p_x);
        Node start = std::make_pair(m_y, m_x);
        std::vector<Node> path =
            BFirstSearch::Path(start, end, monster_window);
        if (path.size() > 1) {
            int random_step = rand() % 2;
            mvwaddch(monster_window, m_y, m_x, '.');
            m_y = path.at(random_step).first;
            m_x = path.at(random_step).second;

            wattron(monster_window, COLOR_PAIR(this->color));
            mvwaddch(monster_window, m_y, m_x, this->body);
            wattroff(monster_window, COLOR_PAIR(this->color));
            Ncurses::update_window(monster_window);
        }
        else {

        }
    }
}

/*
 * puts the Monsters on random position
 * on the screen
 */
void Monster::monster_generate_drop() {
    random_loot = rand() % 1;
    if (random_loot == 1) {
        random_index = rand() % life_drop.size() -1;
        drop = life_drop.at(random_index);
    } else {
        random_index = rand() % armor_drop.size() -1;
        drop = armor_drop.at(random_index);
    }
}
/*
 * the attack of the enemy based on the enemy strength
 */ 
int  Monster::monster_attack() {
    int enem_random_attack = rand() % this->power;
    return enem_random_attack;
}
/*
 * generates the enemies  position
 */ 
void Monster::monster_generate_pos() {
    srand(time(NULL));
    int tmp_y, tmp_x;
    do {
        tmp_y = rand() % (LINES -1);
        tmp_x = rand() % (COLS -1);
    } while (mvwinch(monster_window, tmp_y, tmp_x) != '.');
    m_y = tmp_y;
    m_x = tmp_x;
    mvwaddch(monster_window, tmp_y, tmp_x, body);
    Ncurses::update_window(monster_window);
}
/*
 * returns true if player is within proximity.
 */
bool Monster::monster_player_proximity() {
    if (mvwinch(monster_window, m_y-1, m_x) == '@') {
        return true;
    }
    if (mvwinch(monster_window, m_y+1, m_x) == '@') {
        return true;
    }
    if (mvwinch(monster_window, m_y, m_x-1) == '@') {
        return true;
    }
    if (mvwinch(monster_window, m_y, m_x+1) == '@') {
        return true;
    }
    if (mvwinch(monster_window, m_y+1, m_x+1) == '@') {
        return true;
    }
    if (mvwinch(monster_window, m_y-1, m_x-1) == '@') {
        return true;
    }
    if (mvwinch(monster_window, m_y+1, m_x-1) == '@') {
        return true;
    }
    if (mvwinch(monster_window, m_y-1, m_x)   == '@') {
        return true;
    } else {
        return false;
    }
}
void Monster::monster_dies() {
    wattron(monster_window, COLOR_PAIR(RED_COL));
    mvwaddch(monster_window, m_y, m_x, body);
    wattroff(monster_window, COLOR_PAIR(RED_COL));
    Ncurses::update_window(monster_window);
}
