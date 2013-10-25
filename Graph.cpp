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
  Node::Node() :
      color(false)
  {
  }
  Node::Node(const Board& i) :
      Robots(i.getRobots()), edges(), color(false)
  {

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
  inline bool
  operator<(const Node& a, const Node& b)
  {
    if (a.hash() < b.hash())
      return true;
    else
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

  }
  void
  Graph::PopulateNodes(const Board& i, unsigned int depth)
  {
    Node n = Node(i);

    //if it does not exist on the hashtable, then make sure to put it on the list and
    //insert it to the hashtable
    if (!sets.get(n))
      {
        nodes.push_back(n);
        //pass it a reference to the node
        sets.put(nodes.back());
      }
    if (depth > 0)
      for (int c = 0; c < i.numRobots(); c++)
        for (int d = 0; d < 4; d++)
          {
            Board tmp = i;
            //if the robot can move in this direction,
            if (tmp.moveRobot(c, d))
              {
                /***
                 * create the element in the list and add the various thingies to the graph.
                 * Also, Boom, Recursion!
                 ***/
                PopulateNodes(tmp, depth - 1);
                //take the resulting board and get a pointer to the representative element
                //made in the previous step
                Node* tmpref = const_cast<Node*>(sets.get(Node(tmp)));
                //check it to make sure that my bugs aren't showing
                if (tmpref)
                  {
                    //and finally, push the reference onto the list of edges,

                    //since we have shown that we can access it.
                    n.edges.push_back(tmpref);
                  }
              }
          }

  }
  const std::list<Node>&
  Graph::getNodes() const
  {
    return this->nodes;
  }
} /* namespace white */
