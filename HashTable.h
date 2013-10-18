/*
 * HashTable.h
 *
 *  Created on: Oct 12, 2013
 *      Author: awhite
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include "Node.h"
#include <vector>
namespace white
{

  class HashTable
  {

    /*
     * Acts like the average linked list node.
     * Contains the node itself and a pointer to the next,
     *  which is probably what you should expect anyway
     *
     */
    class node
    {
    public:
      node *next;
      Node *value;

    };
    /**
     * Stores all of the nodes in the hashtable in case of catastrophic deletion fuckups.
     */
    std::vector<node*> completerecords;
    /**
     * controls the amount that it is expanded by when necessary
     * Should be set to something like 1.75;
     */
    float expansionfactor;
    unsigned int msize;
    node **mdata;
    //if this is true, then it will resize array next time there is a need for it.
    bool needsresize;
    void
    initializeArray();
  public:
    /**
     * For I fear that this may be required.
     * Let us hope that it is not.
     */

    HashTable(unsigned int capacity = 100, float expansion = 1.75);
    virtual
    ~HashTable();
    /**
     * returns true if it exists;
     */
    bool
    put(const Node& i);
    //get the pointer to the element in the hashtable, if it exists at all.
    const white::Node*
    get(const Node&) const;
    /**
     * Increases the size to size*expansion
     */
    void
    resize();
  };

} /* namespace white */
#endif /* HASHTABLE_H_ */
