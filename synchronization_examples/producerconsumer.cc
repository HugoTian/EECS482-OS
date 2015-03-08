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

const int BUFSIZE = 5;
char buffer[BUFSIZE];       //  buffer here.
int start = 0;              // Points to first filled location if 
                            // buffer non-empty.
int end = 0;                // Points to next available location.

// State variables to track current status of buffer.

int bufitemcount;



// Locks and condition variables.
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t OKToProduce = PTHREAD_COND_INITIALIZER;
static pthread_cond_t OKToConsume = PTHREAD_COND_INITIALIZER;


void *producer(void *arg);
void *consumer(void *arg);
void produceItem(char c);
char consumeItem();


main()
{
  pthread_t pid;
  pthread_t cid;
  int arg = 0;
  int error;

  // Initialize state variables

  bufitemcount = 0;
   
  if (error = pthread_create(&pid, NULL, producer, &arg)) {
      cerr << "Failed to create producer thread: " << strerror(error) 
	   << endl;
        exit(1);
  } 

  if (pthread_create(&cid, NULL, consumer, &arg)) {
	cerr << "Failed to create consumer thread: " << strerror(error) 
	   << endl;
        exit(1);
  }

  // Detach threads. Main not going to wait on them.
  if (error = pthread_detach(pid)) {
      cerr << "Failed to detach producer thread: " << strerror(error) << endl;
      exit(1);
  }
  if (error = pthread_detach(cid)) {
      cerr << "Failed to detach cosumer thread: " << strerror(error) << endl;
      exit(1);
  }

  pthread_exit(0);   // Cannot just exit. Else process dies.

}


void *producer(void *arg)
{
    char c;
    cout << "Enter input for the producer terminated by control-D" << endl;
    while (cin >> c) {
	produceItem(c);
	randomdelay();       // to simplify testing with non-determinism
    }

    produceItem((char) -1);    // terminator
    return 0;
}


void *consumer(void *arg)
{
    char c;
    while (1) {
	randomdelay();       // to simplify testing with non-determinism
	c = consumeItem();
	if (c == -1) return 0;
    }
    produceItem(-1);    // terminator
}


void produceItem(char c)
{
    // START OF CRITICAL SECTION CODE
    pthread_mutex_lock(&mutex);  
    while (bufitemcount == BUFSIZE) {      // Scheduling constraint
	pthread_cond_wait(&OKToProduce, &mutex);
    }
    assert(bufitemcount < BUFSIZE);       // Optional Sanity check.

    buffer[end] = c;               // Update the buffer.
    end = (end+1) % BUFSIZE;
    bufitemcount++;
    if (c != -1) cout << "item produced = " << c << endl;

    pthread_cond_signal(&OKToConsume); // wake up the consumer
    pthread_mutex_unlock(&mutex);
    // END OF CRITICAL SECTION CODE
}

char consumeItem()
{
    char c;
    // START OF CRITICAL SECTION CODE
    pthread_mutex_lock(&mutex);  
    while (bufitemcount == 0) {      // Scheduling constraint
	pthread_cond_wait(&OKToConsume, &mutex);
    }
    assert(bufitemcount > 0);       // Optional Sanity check.

    c = buffer[start];               // Update the buffer.
    start = (start+1) % BUFSIZE;
    bufitemcount--;

    cout << endl << "item consumed = " << c << endl;

    
    pthread_cond_signal(&OKToProduce); // wake up the consumer
    pthread_mutex_unlock(&mutex);
    // END OF CRITICAL SECTION CODE
    return c;
}
    
	

    
    






