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
#include "Graph.h"
#include <vector>
#include <queue>
#include <map>
namespace white{
  std::queue<command> find_path_bfs(const Graph&);
};



#endif /* PATHFINDING_H_ */
