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
#include <ncurses.h>
#include <vector>

#include "player.hpp"
// #include "types.hpp"
#include "ncurses.hpp"
#include "monster.hpp"

Player::Player(WINDOW *win) {
    this->is_alive = true;
    this->ypos = 10;
    this->xpos = 2;
    this->player_strength = 3;
    this->player_life = 10;
    this->win = win;

    //Ncurses::update_life_point(win, player_life);

}
bool Player::get_moved_state() {
    return state;
}
void Player::set_moved_state(bool new_state) {
    state = new_state;
}

void Player::attach(Monster *mon) {
    monsters.push_back(mon);
} 
void Player::detach(Monster *mon) {
    auto it = std::find(monsters.begin(), monsters.end(), mon);
    if (it != monsters.end()) {
        monsters.erase(it);
        delete mon;
    }
}
void Player::notify_monsters_moved() {
    for (Monster* mon : monsters) {
        mon->monster_update(ypos, xpos);
    }
}

bool Player::notify_monsters_attack() {
    for (Monster* mon : monsters) {
        if (PLayerWithinProximity(mon->monster_getter_pos())) {
            int damage  = mon->monster_attack();
            player_life =  player_life - damage;
            Ncurses::update_life_point(this->win, player_life);
            Ncurses::update_window(this->win);
            if (player_life == 0) {
                is_alive = false;
                return true;
            }
        }
    }
    return false;
}
/*
 * returns true if there is a proper way of moving
 */
bool Player::PlayerCanBeMove(WINDOW *win,int in) {
    if (in == KEY_RIGHT && mvwinch(win, ypos, xpos + 1) != '#') {
        return true;
    }
    if (in == KEY_UP && mvwinch(win, ypos - 1, xpos) != '#') {
        return true;
    }
    if (in == KEY_DOWN && mvwinch(win, ypos + 1, xpos) != '#') {
        return true;
    }
    if (in == KEY_LEFT && mvwinch(win, ypos, xpos - 1) != '#') {
        return true;
    } else {
        return false;
    }
}

/*
 * updates the given player positions
 */
void Player::PlayerMove(int in) {
    if (in == KEY_RIGHT) {
        xpos++;
    }
    if (in == KEY_UP) {
        ypos--;
    }
    if (in == KEY_DOWN) {
        ypos++;
    }
    if (in == KEY_LEFT) {
        xpos--;
    }
}

/*
 * returns true if player within proximity
 */
bool Player::PLayerWithinProximity(Node enemy_pos) {
    if ((enemy_pos.second -1 == xpos) && (enemy_pos.first == ypos)) {
        return true;
    }
    if ((enemy_pos.second +1 == xpos) && (enemy_pos.first == ypos)) {
        return true;
    }
    if ((enemy_pos.second  == xpos) && ((enemy_pos.first -1) == ypos)) {
        return true;
    }
    if ((enemy_pos.second == xpos) && ((enemy_pos.first +1) == ypos)) {
        return true;
    } else {
        return false;
    }
}

/*
int Player::PlayerAttack(WINDOW *win, Node
        enemy_pos, int enemy_health, char monster_body) {
    int enemy_setter = enemy_health;
    int random_attack = rand() % Player::player_strength;
    if (Player::PLayerWithinProximity(enemy_pos)) {
        if (enemy_health == 1) {
            enemy_setter = enemy_health- random_attack;
            wattron(win, COLOR_PAIR(DEAD_COL));
            mvwaddch(win, enemy_pos.first, enemy_pos.second, monster_body);
            wattroff(win, COLOR_PAIR(DEAD_COL));
            Ncurses::update_window(win);
        } else {
        }
    }
    return enemy_setter;
}
*/

void Player::PlayerUpdate(WINDOW *win, int in) {
    if (PlayerCanBeMove(win,in) && is_alive ) {
        mvwaddch(win, ypos, xpos, '.');
        PlayerMove(in);
    }
    unsigned int current_char = mvwinch(win, ypos, xpos);
    if (current_char == '.') {
        mvwaddch(win, ypos, xpos, '@');
        refresh();
        wrefresh(win);
    }
}
