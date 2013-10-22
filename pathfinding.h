/*
 * pathfinding.h
 *
 *  Created on: Oct 21, 2013
 *      Author: awhite
 */

#ifndef PATHFINDING_H_
#define PATHFINDING_H_
#include "board.h"
#include "command.h"
#include <vector>
#include <queue>
#include <map>
bool find_path_bfs(const Board&,int,std::vector<command>&);



#endif /* PATHFINDING_H_ */
