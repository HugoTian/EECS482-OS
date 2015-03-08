/*
 * Author: Atul Prakash, Department of EECS, University of Michigan, Ann Arbor, MI 48109
 * copyright (c) 2006 Atul Prakash
 *
 */

#include "randomdelay.h"

void randomdelay()
{
  
  char val;
  int fd = open("/dev/urandom" , O_RDONLY);
  read(fd, &val, 1); // read a random byte into val
  struct timespec sleeptime;
  sleeptime.tv_sec = 0;
  sleeptime.tv_nsec = (int) val;
  nanosleep(&sleeptime, NULL);
}
