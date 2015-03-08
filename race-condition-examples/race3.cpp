/*
 * Author: Atul Prakash, Department of EECS, University of Michigan, Ann Arbor, MI 48109
 * copyright (c) 2006 Atul Prakash
 *
 */

#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include "randomdelay.h"
using namespace std;

int A = 2;
int B = 3; 
void *thread2code(void *arg);

main()
{
  pthread_t tid;
  int arg = 0;
  int error;
   
  if (pthread_create(&tid, NULL, thread2code, &arg)) {
        cerr << "Failed to create thread" << endl;
        exit(1);
  } 

  // FIRST THREAD 
  A = B;
  randomdelay();
  if (A == B) cout << "they are equal. A = " << A << " B = " << B << endl;
  else cout << "they are not equal. A = " << A << " B = " << B << endl;
}

void *thread2code(void *arg)
{
   // SECOND THREAD
   randomdelay();
   B = A+1;
}
