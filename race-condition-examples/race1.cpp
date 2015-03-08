/*
 * Author: Atul Prakash, Department of EECS, University of Michigan, Ann Arbor, MI 48109
 * copyright (c) 2006 Atul Prakash
 *
 */

#include <iostream>
#include <sys/wait.h>

void output1();
void output2();

// This may not show race conditions because of fast machines

using namespace std;

int main()
{
   int status;

   switch (fork()) 
   { 
      case -1: 
	perror("fork failed"); 
	exit(1);
      case 0: 
     	output2();     // Child process. Gets 0 as return val. for fork
	exit(0);
      default:          
	output1();    // Parent process. gets child pid as return value.
        wait(&status); // wait for the child to exit
        exit(0);
   }
}

void output1()
{
   cout << "PARENT: A" << endl; 
   cout << "PARENT: B" << endl; 
   cout << "PARENT: C" << endl;
}

void output2()
{
   cout << "CHILD: D" << endl; 
   cout << "CHILD: E" << endl; 
   cout << "CHILD: F" << endl; 
}
