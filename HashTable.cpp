/*
 * HashTable.cpp
 *
 *  Created on: Oct 12, 2013
 *      Author: awhite
 */

#include "HashTable.h"
#include <cstdlib>
namespace white
{

  void
  HashTable::initializeArray()
  {
    mdata = new node*[msize];
    for (unsigned long i = 0; i < msize; i++)
      {
        mdata[i] = (node*) 0;
      }

  }
  HashTable::HashTable(unsigned int capacity, float expansion) :
      expansionfactor(expansion), msize(capacity), mdata((node**) 0), needsresize(
          false)
  {


  }

  HashTable::~HashTable()
  {
    delete[] mdata;
  }
  bool
  HashTable::put(const Node& c)
  {
    //stores the number of collisions encountered
    unsigned short count = 0;
    //the index is defined by the applying modulo to the hash of the element,
    unsigned long index = c.hash() % msize;
    //collision, or the state already exists
    if (mdata[index])
      { //make a temporary variable to store the current node.
        node* cur = mdata[index];
        while (cur->next)
          {
            count++;
            //if it does in fact exist, there is no reason to allocate any memory whatsoever.
            if (*cur->value == c)
              return true;
            cur = cur->next;
          }
        cur->next = new node;
        completerecords.push_back(cur->next);
        cur->next->value = const_cast<Node*>(&c);
        return false;
      }
    else
      return false;
  }
  void
  HashTable::resize()
  {
    node** tmpdata;
    unsigned int nsize = (unsigned int) msize * expansionfactor;
    //Yeah! Allocate that memory!
    tmpdata = new node*[nsize];
    //initialize new pointers to NULL
    for (unsigned int i = 0; i < nsize; ++i)
      {
        tmpdata[i] = NULL;
      }
    for (unsigned int i = 0; i < completerecords.size(); ++i)
      {
        node* g = completerecords[i];
        if (tmpdata[g->value->hash() % nsize])
          {
            node* ttmp = tmpdata[g->value->hash() % nsize];
            while (ttmp->next)
              {
                ttmp = ttmp->next;
              }
            ttmp->next = g;
            g->next = NULL;
          }
      }
    msize = nsize;
    //free the memory
    delete[] mdata;
    mdata = tmpdata;
  }
  const Node*
  HashTable::get(const Node& c) const
  {
    Node d;
    node *e;
    for (e = mdata[c.hash() % msize]; e; e = e->next)
      {
        if (*e->value == c)
          return e->value;
      }
    return (Node*) 0;
  }
} /* namespace white */
