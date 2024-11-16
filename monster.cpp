// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <utility>
#include <vector>

#include "monster.hpp"
#include "ncurses.hpp"
#include "breadthFirstSearch.hpp"

std::vector<int> life_drop  = {10, 15, 30};
std::vector<int> armor_drop = {8, 10, 5};
int random_loot, random_index, drop;


Monster::Monster(int _id, WINDOW *win, Player *pl, std::string name, int power, char body, int color) {
    this->is_dead = false;
    this->_id = _id;
    this->player = pl;
    this->monster_name = name;
    this->power = power;
    this->color = color;
    this->body = body;
    this->win = win;
    life = 13;
    monster_name = name;
}

void Monster::monster_update(int p_y, int p_x) {
    if ( (life >0) && (!is_dead)) {
        Node  end = std::make_pair(p_y, p_x);
        Node start = std::make_pair(m_y, m_x);
        std::vector<Node> path = BFirstSearch::Path(start, end, win);
        if (path.size() > 1) {
            int random_step = rand() % 2;
            mvwaddch(win, m_y, m_x, '.');
            m_y = path.at(random_step).first;
            m_x = path.at(random_step).second;

            wattron(win, COLOR_PAIR(this->color));
            mvwaddch(win, m_y, m_x, this->body);
            wattroff(win, COLOR_PAIR(this->color));
            Ncurses::update_window(win);
        }
    }
}

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
int  Monster::monster_attack() {
    int enem_random_attack = rand() % this->power;
    return enem_random_attack;
}
void Monster::monster_generate_pos() {
    srand(time(NULL));
    int tmp_y, tmp_x;
    do {
        tmp_y = rand() % (LINES);
        tmp_x = rand() % (COLS);
    } while (mvwinch(win, tmp_y, tmp_x) != '.');
    m_y = tmp_y;
    m_x = tmp_x;
    mvwaddch(win, tmp_y, tmp_x, body);
    Ncurses::update_window(win);
}
bool Monster::monster_player_proximity() { if (mvwinch(win, m_y-1, m_x) == '@') { return true;
    }
    if (mvwinch(win, m_y+1, m_x) == '@') {
        return true;
    }
    if (mvwinch(win, m_y, m_x-1) == '@') {
        return true;
    }
    if (mvwinch(win, m_y, m_x+1) == '@') {
        return true;
    }
    if (mvwinch(win, m_y+1, m_x+1) == '@') {
        return true;
    }
    if (mvwinch(win, m_y-1, m_x-1) == '@') {
        return true;
    }
    if (mvwinch(win, m_y+1, m_x-1) == '@') {
        return true;
    }
    if (mvwinch(win, m_y-1, m_x)   == '@') {
        return true;
    } else {
        return false;
    }
}
void Monster::monster_dies() {
    is_dead = true;
    wattron(win, COLOR_PAIR(RED_COL));
    mvwaddch(win, m_y, m_x, '%');
    wattroff(win, COLOR_PAIR(RED_COL));
    Ncurses::update_window(win);
}
