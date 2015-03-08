/*
 * Author: Atul Prakash, Department of EECS, University of Michigan, Ann Arbor, MI 48109
 * copyright (c) 2006 Atul Prakash
 *
 */

#include <iostream>
#include <sys/wait.h>
#include "randomdelay.h"

void output1();
void output2();

using namespace std;

int main()
{
   int status;

   switch (fork()) 
   { 
      case -1: 
	perror("fork"); // something wrong
	exit(1);
      case 0: 
     	output2();
	exit(0);
      default:
	output1();
        wait(&status); // wait for the child to exit
        exit(0);
   }
}

void output1()
{
   randomdelay();
   cout << "PARENT: A" << endl; 
   randomdelay();
   cout << "PARENT: B" << endl; 
   randomdelay();
   cout << "PARENT: C" << endl;
}

void output2()
{
   randomdelay();
   cout << "CHILD: D" << endl; 
   randomdelay();
   cout << "CHILD: E" << endl; 
   randomdelay();
   cout << "CHILD: F" << endl; 
}
