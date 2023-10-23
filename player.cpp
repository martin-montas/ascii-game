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
    this->is_alive = true;
    this->ypos = 10;
    this->xpos = 2;
    this->player_strength = 3;
    this->player_life = 10;
    this->win = win;

    pstatus = STATUS_ALIVE;
    // Ncurses::update_life_point(win, player_life);

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
        if (PLayerWithinProximity(mon->monster_getter_pos())) {
            int damage  = mon->monster_attack();
            player_life =  player_life - damage;
            Ncurses::update_life_point(this->win, player_life);
            Ncurses::update_window(this->win);
            if (player_life == 0) {
                pstatus = STATUS_DIED;
                // make bool maybe later
                //return true;
            }
        }
    }
    //return false;
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

void Player::player_attack(WINDOW *win) {

    //int enemy_setter = enemy_health;
    int random_attack = rand() % player_strength;
    for(Monster *mon: monsters) {
    if (Player::PLayerWithinProximity(mon->monster_getter_pos())) {
        int new_enemy_health = mon->monster_getter_life();
        new_enemy_health -= random_attack;
        mon->monster_dies();
        mon->monster_setter_life(new_enemy_health);
        Ncurses::update_window(win);

    }

    }
}

void Player::PlayerUpdate(WINDOW *win, int in) {
    if (PlayerCanBeMove(win,in) && pstatus != STATUS_DIED) {
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
