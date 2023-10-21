// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#include <curses.h>
#include <ncurses.h>
#include <panel.h>
#include <vector>
#include <utility>

#include "game.hpp"
#include "window.hpp"
#include "ncurses.hpp"
#include "types.hpp"

Game::Game() {

    Ncurses::init_colors();

    game_over   = false;
    m_win       = win.Init(1, 1);
    m_panel     = new_panel(m_win);
    player      = new Player(m_win);

    Ncurses::draw_map("./map/map02.txt", m_win);
    Ncurses::update_Level(m_win, 1);
    Ncurses::update_strength_point(m_win, 30);
    Ncurses::set_player_sees(m_win);
    Ncurses::set_window_command(m_win);
    wrefresh(m_win);
    ustatus = STATUS_PLAYING;

}

Game::~Game() {
    wclear(ext_win);
    del_panel(ext_panel);
    delwin(ext_win);
    for(auto *m: monsters) {
        delete m;
    }

    delete player;
    monsters.clear();
}

int in;
int w_in;
void Game::Run() {

    level00();

    /* main loop */
    do  {
        switch((in = wgetch(m_win)))  {
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

                player->PlayerUpdate(m_win,in);
                player->notify_monsters_moved();
                player->notify_monsters_attack();

                wrefresh(m_win);
                break;

            case ' ': // do nothing for now TODO

            case 'q':
                ext_win    = Ncurses::exit_win(m_win);
                ext_panel  = new_panel(ext_win);
                w_in = wgetch(ext_win);
                if (w_in == 'y') {
                    ustatus =  STATUS_QUIT;
                }
                if (w_in == 'n') {
                    top_panel(m_panel);
                    update_panels();
                } else {
                    continue;
                }
                break;

            default:
                continue;
            }
    } while(ustatus != STATUS_QUIT);
}

void Game::game_alert_resize() {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    if (rows <= 25) {
        mvprintw(1, 1, "You shouldn't resize this far.");
        refresh();
    }
    else {
        return;
    }
}

void Game::level00() {
    Monster *mon    = new Monster(m_win, player, "orc", 2, 'o', GREEN_COL);
    Monster *mon_2  = new Monster(m_win, player, "orc", 2, 'o', GREEN_COL);

    // to keep track of the monsters 
    player->attach(mon);
    player->attach(mon_2);

    // for deletion on the destructor
    monsters.push_back(mon);
    monsters.push_back(mon_2);

}

void Game::handle_exit_win(int in) {
        while((in = wgetch(ext_win))) {
        if (in == 'n') {
            wclear(ext_win);
            top_panel(m_panel);
            wrefresh(ext_win);
        }
        else {
        resizeterm(LINES,COLS);
        }
    }
}
