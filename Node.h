/*
 * Node.h
 *
 *  Created on: Oct 17, 2013
 *      Author: awhite
 */

#ifndef NODE_H_
#define NODE_H_
#include <vector>
#include "board.h"
namespace white
{
  class Node
  {
  public:
    friend class Board;
    std::vector<Position> Robots;
    std::vector<Node*> edges;
    bool color;
    //this is going to be a long function
    unsigned int
    hash() const;
  };
  bool
  operator==(const Node& a, const Node& b);
  inline bool
  operator<(const Node& a, const Node& b);
}

#endif /* NODE_H_ */
