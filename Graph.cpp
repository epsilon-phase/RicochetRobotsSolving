/*
 * Graph.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: awhite
 */

#include "Graph.h"

namespace white
{
  unsigned int
  Node::hash() const
  {
    std::vector<unsigned short> nbytes;
    std::vector<unsigned short> tmp;

    for (unsigned int i = 0; i < Robots.size(); i++)
      {
        tmp = castToBytes(Robots[i].col);
        for (unsigned int c = 0; c < tmp.size(); c++)
          nbytes.push_back(tmp[c]);
        tmp = castToBytes(Robots[i].row);
        for (unsigned int c = 0; c < tmp.size(); c++)
          nbytes.push_back(tmp[c]);
      }

    //adler32 hash
    unsigned int a = 1, b = 0;
    for (unsigned int i = 0; i < nbytes.size(); ++i)
      {
        a = (a + nbytes[i]) % 65521;
        b = (b + a) % 65521;
      }
    return (b << 16) | a;

  }
  bool
  operator==(const Node& a, const Node& b)
  {
    if (a.Robots.size() == b.Robots.size())
      {
        for (unsigned int c = 0; c < a.Robots.size(); c++)
          {
            if (a.Robots[c] != b.Robots[c])
              return false;
          }
        return true;
      }
    return false;
  }
  Graph::Graph() :
      begin(NULL), robotgoal(-1)
  {
  }
  Graph::Graph(const Board& c)
  {
    this->robotgoal = c.getGoalRobot();
    Node a;
    a.Robots = std::vector<Position>(c.getRobots());
    nodes.push_back(a);
    begin = &nodes.front();
  }
  Graph::Graph(const Node& i) :
      begin(NULL), robotgoal(-1)
  {
    this->nodes.push_back(i);
    begin = &nodes.front();
  }

  Graph::~Graph()
  {
// TODO Auto-generated destructor stub
  }
  void Graph::PopulateNodes(const Board& i,unsigned int depth){

  }

} /* namespace white */
