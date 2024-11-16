// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//

#ifndef WINDOW_HPP_
#define WINDOW_HPP_
#include <ncurses.h>

class Window{

 public:
        WINDOW * Init(int y, int x);
        void update_strength_point(int point);
        void set_player_sees();
        void set_window_command();

 private:
        WINDOW *win;
};
extern int width, height;

#endif   // WINDOW_HPP_
