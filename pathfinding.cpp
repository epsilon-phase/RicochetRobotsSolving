/*
 * pathfinding.cpp
 *
 *  Created on: Oct 21, 2013
 *      Author: awhite
 */

#include "pathfinding.h"
using namespace std;
namespace white
{
//use breadth first search to find the shortest move set.
  bool
  find_path_bfs(const Graph& g,vector<command> &out)
  {
    queue<const Node*> d;
    Node *solution;
    //queue the nodes
    for(list<Node>::const_iterator c=g.getNodes().begin();c!=g.getNodes().end();c++){
        d.push(&(*c));
    }
    while(!d.empty()){}

  }
};
