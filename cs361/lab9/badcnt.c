/* This program is a template of lab9 
	function: try to create and join two sets of threads 
		then count all the thread
		It is an improperly synchronized counter program. 

	try to find all the ... part and fill the gap with comment instructions

	compilation command : gcc -pthread -o badcnt badcnt_Template.c
	running command argument: try different value starting from 1
*/



/* 0. add proper library*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


void *countingThread(void *vargp); // thread rountine prototype 

volatile long cnt = 0; //counter: global shared variable

int main(int argc, char **argv){

	long niters; //the thread number from argument
	pthread_t tid1, tid2;

	if(argc != 2){//check input argument
		printf("%s %s %s\n", "usage:", argv[0], " <niters>");
		exit(0);
	}

	niters = atoi(argv[1]);

	//create threads and wait for them to finish
	/* 1. create and launch two threads running the countingThread function
		(hint: pthread_create())
	*/
  long work1 = niters/2;
  long work2 = niters-work1;
	pthread_create(&tid1, 0, countingThread, &work1);
	pthread_create(&tid2, 0, countingThread, &work2);
	/* 2. join the two threads
		(hint: pthread_join())
	*/
	pthread_join(tid1, 0);
  pthread_join(tid2, 0);


	//check result
	if(cnt != (niters))
		printf("BOOM! cnt = %ld\n", cnt);
	else
		printf("OK cnt = %ld\n", cnt);

	exit(0);

}

//thread rountine
void *countingThread(void *vargp){

	/*3. increments cnt using the ++ operator 
		as many times as the integer argument passed in, 
		then returns NULL.*/
	int i;
  long niters = *((long *)vargp);
  printf("debug: %li\n", niters);
  for (i=0; i<niters; i++) {
    cnt++;
  }
  return NULL;
}

/* 4(optional). after you finish this program:
	try to find the correlation between the number of threads and 
		the degree of error encountered. 
	(hint: make the number of threads a variable
		use array to store and track all threads IDs)
*/

/* 5(optional). after finished 4, 
	add a mutex semaphore around cnt++ line
	(hint: HW5)
*/
