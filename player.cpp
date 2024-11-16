// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#include <ncurses.h>
#include <vector>
#include <cstdlib>


#include "player.hpp"
#include "ncurses.hpp"
#include "monster.hpp"

Player::Player(WINDOW *win) {
    this->player_strength = 3;
    this->player_life = 10;
    this->win = win;

    pstatus = STATUS_ALIVE;
}
void Player::generate_player_pos() {
    int tmp_y, tmp_x;
    do {
        tmp_y = rand() % (LINES);
        tmp_x = rand() % (COLS);
    } while (mvwinch(win, tmp_y, tmp_x) != '.');
    ypos = tmp_y;
    xpos = tmp_x;
    mvwaddch(win, tmp_y, tmp_x, '@');
    Ncurses::update_window(win);
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

void Player::notify_monsters_move() {
    for (Monster* mon : monsters) {
        mon->monster_update(ypos, xpos);
    }
}


void Player::notify_monster_hit() {
    for (Monster* mon : monsters) {
        if (player_proximity(mon->monster_getter_pos())) {
            int damage  = mon->monster_attack();
            player_life =  player_life - damage;
            Ncurses::update_life_point(this->win, player_life);
            Ncurses::update_window(this->win);
            if (player_life == 0) {
                pstatus = STATUS_DIED;
                // make bool maybe later
                // return true;
            }
        }
    }
    // return false;
}

bool Player::player_can_move(int in) {
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

void Player::player_move(int in) {
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
bool Player::player_proximity(Node enemy_pos) {
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

bool Player::notify_all_monster_life() {
    for (Monster *mon : monsters) {
        if (!mon->is_dead) 
            return false;
    }
    return true;
}



void Player::player_attack() {
    int random_attack = rand() % player_strength;
    for (Monster *mon : monsters) {
    if (Player::player_proximity(mon->monster_getter_pos()) && (!mon->is_dead)) {
        int new_enemy_health = mon->monster_getter_life();
        new_enemy_health -= random_attack;
        mon->monster_setter_life(new_enemy_health);
        if (new_enemy_health == 0) {
            mon->monster_dies();
        }
        Ncurses::update_window(win);
        }
    }
}

void Player::player_update(int in) {
    if (player_can_move(in) && pstatus != STATUS_DIED) {
        mvwaddch(win, ypos, xpos, '.');
        player_move(in);
    }
    unsigned int current_char = mvwinch(win, ypos, xpos);
    if (current_char == '.') {
        mvwaddch(win, ypos, xpos, '@');
        refresh();
        wrefresh(win);
    }
}
