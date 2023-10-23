
// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
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
