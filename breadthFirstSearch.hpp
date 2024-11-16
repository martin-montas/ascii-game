// Copyright 2022 Robot Locomotion Group @ CSAIL. All rights reserved.
// All components of this software are licensed under the GNU License.
// Programmer: Martin Montas, martinmontas1@gmail.com
//
#ifndef BREADTHFIRSTSEARCH_HPP_
#define BREADTHFIRSTSEARCH_HPP_

#include <ncurses.h>
#include <vector>
#include <utility>
typedef std::pair<int, int> Node;
namespace BFirstSearch {
    std::vector<Node> Path(Node start, Node end, WINDOW *win);
    std::vector<Node> GetNeighbours(Node node, WINDOW *win);
};
#endif  //  BREADTHFIRSTSEARCH_HPP_
