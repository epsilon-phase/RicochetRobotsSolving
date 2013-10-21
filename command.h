/*
 * command.h
 *
 *  Created on: Oct 21, 2013
 *      Author: awhite
 */

#ifndef COMMAND_H_
#define COMMAND_H_
struct command
{

  command(char c, unsigned short d) :
      robot(c), dir(d)
  {
  }
  char robot;
  unsigned short dir;
}typedef command;



#endif /* COMMAND_H_ */
