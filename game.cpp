// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
#include <curses.h>
#include <ncurses.h>
#include <panel.h>
#include <time.h>

#include <vector>
#include <cstdlib>
#include <string>

#include "game.hpp"
#include "monster.hpp"
#include "window.hpp"
#include "ncurses.hpp"

#define MAX_MONSTER  4

std::vector<std::string> map_order = {
     "./map/map02.txt",
     "./map/map03.txt"
};

int in;
int w_in;
int m_ind;
Game::Game() {
     game_over   = false;
     Ncurses::init_colors();
     m_win       = window.Init(1, 1);
     m_panel     = new_panel(m_win);
     window.set_player_sees();
     window.set_window_command();
     player      = new Player(m_win);
     m_ind       = 0;
     Ncurses::draw_map(map_order.at(m_ind), m_win);
     Ncurses::update_Level(m_win, 1);
     wrefresh(m_win);
     ustatus = STATUS_PLAYING;
}
Game::~Game() {
     wclear(ext_win);
     del_panel(ext_panel);
     delwin(ext_win);
     for (auto *m : monsters) {
          delete m;
     }
     delete player;
     monsters.clear();
}

void Game::Run() {
     player->generate_player_pos();
     generate_monster_group();

     /* MAIN LOOP */
     do  {
          switch ((in = wgetch(m_win))) {
               case KEY_RESIZE:
                    game_alert_resize();
                    top_panel(m_panel);
                    update_panels();
                    getch();
                    break;
               case KEY_UP:
               case KEY_RIGHT:
               case KEY_LEFT:
               case KEY_DOWN:
                    player->player_update(in);
                    player->notify_monsters_move();
                    player->notify_monster_hit();
                    wrefresh(m_win);
                    break;
               case ' ':  // this is the attack key
                    player->player_attack();
                    change_map = player->notify_all_monster_life();
                    if (change_map) {
                         wclear(m_win);
                         m_ind += 1;
                         Ncurses::draw_map(map_order.at(m_ind), m_win);
                         player->generate_player_pos();
                         wrefresh(m_win);
                    }
                    break;
               case 'q':
                    ustatus = STATUS_PAUSED;
                    keypad(m_win, FALSE);
                    ext_win    = Ncurses::exit_win(m_win);
                    ext_panel  = new_panel(ext_win);
                    w_in = wgetch(ext_win);
                    if (w_in == 'y') {
                         ustatus =  STATUS_QUIT;
                    }
                    if (w_in == 'n') {
                         ustatus = STATUS_PLAYING;
                         keypad(m_win, TRUE);
                         top_panel(m_panel);
                         update_panels();
                    } else {
                         continue;
                    }
                    break;
               default:
                    continue;
          }
     } while (ustatus != STATUS_QUIT);
}

void Game::game_alert_resize() {
     int rows, cols;
     getmaxyx(stdscr, rows, cols);
     if (rows <= 25) {
          mvprintw(1, 1, "You shouldn't resize this far.");
          refresh();
     } else {
          return;
     }
}

std::vector<char> monsters_name = {'o', 's', 'm', 'z'};
void Game::generate_monster_group() {
     srand(time(NULL));
     int m_amount =  rand() % MAX_MONSTER;

     if (m_amount == 0)
          m_amount = 1;

     while (m_amount--) {
          char rand_mon = monsters_name.at(rand() % (monsters_name.size() -1));
          switch (rand_mon) {
               case 'o':
                    mon = new Monster(1, m_win, player, "orc", 2, 'o', GREEN_COL);
                    mon->monster_generate_pos();
                    player->attach(mon);
                    monsters.push_back(mon);
                    break;
               case 'm':
                    mon = new Monster(1, m_win, player, "Minotaur", 4, 'M', BLUE_COL);
                    mon->monster_generate_pos();
                    player->attach(mon);
                    monsters.push_back(mon);
                    break;
               case 's':
                    mon     = new Monster(1, m_win, player, "Sphinx", 3, 'S', YELLOW_COL);
                    mon->monster_generate_pos();
                    player->attach(mon);
                    monsters.push_back(mon);
                    break;
               case 'z':
                    mon    = new Monster(1, m_win, player, "Zombie", 3, 'Z', RED_COL);
                    mon->monster_generate_pos();
                    player->attach(mon);
                    monsters.push_back(mon);
                    break;
               default:
                    break;
          }
     }
}

void Game::handle_exit_win(int in) {
     while ((in = wgetch(ext_win))) {
          if (in == 'n') {
               wclear(ext_win);
               top_panel(m_panel);
               wrefresh(ext_win);
          } else {
               resizeterm(LINES, COLS);
          }
     }
}
