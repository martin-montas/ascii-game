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
#ifndef BREADTHFIRSTSEARCH_HPP_
#define BREADTHFIRSTSEARCH_HPP_

#include <ncurses.h>
#include <vector>
#include <utility>
typedef std::pair<int,int> Node;
namespace BFirstSearch {
    std::vector<Node> Path(Node start, Node end, WINDOW *win);
    std::vector<Node> GetNeighbours(Node node, WINDOW *win);
};
#endif  //  BREADTHFIRSTSEARCH_HPP_
