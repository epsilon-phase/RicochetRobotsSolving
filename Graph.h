/*
 * Graph.h
 *
 *  Created on: Oct 11, 2013
 *      Author: awhite
 */

#ifndef GRAPH_H_
#define GRAPH_H_
//#include "board.h"
#include <list>
#include <cstring>
#include <cstdlib>
#include "muutil.h"
#include "HashTable.h"
#include "Node.h"
namespace white
{


  class Graph
  {

    /**
     * The beginning of the graph, the start state of the game, etc.
     */
    Node* begin;
    /**
     * Needs to be a list in order to prevent the pointers from all becoming invalid at once.
     */
    std::list<Node> nodes;
    HashTable da;
    signed char robotgoal;
  public:

    void
    PopulateNodes(const Board&, unsigned int depth);
    //initialize with a given start value.
    Graph(const Node&);
    //get the starting position from the board.
    Graph(const Board&);
    Graph();
    virtual
    ~Graph();
  };

} /* namespace white */
#endif /* GRAPH_H_ */
