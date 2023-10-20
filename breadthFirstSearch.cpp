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
#include <curses.h>
#include <map>
#include <ncurses.h>
#include <queue>
#include "breadthFirstSearch.hpp"
//#include "window.hpp"



std::vector<Node> BFirstSearch::GetNeighbours(Node node, WINDOW *win) {
    std::vector<Node> neighbours;
    int qY  = node.first;
    int qX = node.second;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0 , 1, -1};
    for (int i =0; i < 4; i++) {
        int rr = qY + dr[i];
        int cc =  qX + dc[i];
        if (rr < 0 || cc < 0) {
            continue;
        }
        if (rr >= LINES || cc >= COLS) {
            continue;
        }
        if (mvwinch(win, rr , cc) == '#') {
            continue;
        if (mvwinch(win, rr , cc) == '.') {
            continue;
        }
        } else {
            neighbours.push_back(std::make_pair(rr, cc));
        }
    }
    return neighbours;
    }

std::vector<Node> BFirstSearch::Path(Node start, Node end, WINDOW *win) {
        std::vector<std::vector<bool>> visited;
        for (int i = 0; i < LINES; i++) {
            std::vector<bool> v1;
        for (int j = 0; j < COLS; j++) {
            v1.push_back(false);
        }
            visited.push_back(v1);
        }
        std::queue<Node> queue;
        std::map<Node, Node> parentMap;
        std::vector<Node> path;
        visited.at(start.first).at(start.second) = true;
        queue.push(start);
        parentMap[start] = std::make_pair(-1, -1);

        while (!queue.empty()) {
            Node node = queue.front();
            if (node == end)
                break;
            queue.pop();
            std::vector<Node> Nodes = BFirstSearch::GetNeighbours(node, win);
            for (auto n : Nodes) {
               if (!visited.at(n.first).at(n.second)) {
                    visited.at(n.first).at(n.second) = true;
                    parentMap[n] = node;
                    queue.push(n);
               }
            }
        }
        Node curr = end;
        while (curr.first != -1) {
            path.insert(path.begin(), curr);
            curr = parentMap[curr];
        }
        return path;
    }
