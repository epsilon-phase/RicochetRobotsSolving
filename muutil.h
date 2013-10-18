/*
 * muutil.h
 *
 *  Created on: Oct 11, 2013
 *      Author: awhite
 */

#ifndef MUUTIL_H_
#define MUUTIL_H_
#include <algorithm>
#include <cstdlib>
#include <vector>
/*
 * Use Bullshit magic to cast whatever I have to shorts.
 */
template<class T>
  std::vector<unsigned short>
  castToBytes(T &c)
  {
    std::vector<unsigned short> d;
     unsigned short *u = const_cast<unsigned short *>(reinterpret_cast<const unsigned short*>(&c));
    for (int i = 0; i < sizeof(c) / 2; i++)
      {
        d.push_back(*u);
      }
    return d;
  }

#endif /* MUUTIL_H_ */
