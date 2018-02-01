/*
 * Author: Gregory N. Schmit (gschmi4@uic.edu)
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

struct worker {
	int nBuffers;
	int workerID;
	double sleepTime;
	int semID;
	int mutexID;
	int *buffers;
	int nReadErrors;
};

void *work(void *vargp)
{
	struct worker *worker_info = vargp;
	// sleep(worker_info->sleepTime);
	// printf("I am worker %i.\n", worker_info->workerID);
	// worker_info->buffers[worker_info->workerID] = worker_info->workerID;

	int i, val, val2;
	int read = 2;
	int b = worker_info->workerID;

	for (i=0; i<3*worker_info->nBuffers; i++) {
		// do work
		if (read) {
			// read
			val = worker_info->buffers[b];
			usleep(worker_info->sleepTime * 1000000);
			val2 = worker_info->buffers[b];
			if (val != val2) {
				printf("Error - worker %i sensed that buffer %i changes from %i to %i\n", worker_info->workerID, b, val, val2);
			}
		} else {
			// write
			val = worker_info->buffers[b];
			usleep(worker_info->sleepTime * 1000000);
			val2 = (1 << (worker_info->workerID - 1));
			worker_info->buffers[b] = val + val2;
			printf("worker %i added %i\n", worker_info->workerID, val2);
		}
		// add workerID (wrap)
		b+=worker_info->workerID;
		if (b >= worker_info->nBuffers) { b-=worker_info->nBuffers; }
		if (!read) { read = 2; } else { read--; }
	}

	return NULL;
}

int main(int argc, char **argv)
{
	// general dict
	int i;

	// parse args
	double sleepMin = 1.0;
	double sleepMax = 5.0;
	int randSeed = 0;
	char lock[10];
	strncpy(lock, "-nolock", 8);
	if (argc < 3) {
		printf("Usage: %s nBuffers nWorkers [ sleepMin sleepMax ] [ -lock | -nolock ]\n", argv[0]);
		exit(0);
	}
	int nBuffers = atoi(argv[1]);
	if (nBuffers < 3 || nBuffers > 31) {
		fprintf(stderr, "Fatal: nBuffers should satisfy 2 < nBuffers < 32\n");
		exit(0);
	}
	if (!(nBuffers % 2 && nBuffers % 3 && nBuffers % 5)) {
		fprintf(stderr, "Fatal: nBuffers should be prime\n");
		exit(0);
	}
	int nWorkers = atoi(argv[2]);
	if (nWorkers < 1 || nWorkers >= nBuffers) {
		fprintf(stderr, "Fatal: nWorkers should be >0 and less than nBuffers\n");
		exit(0);
	}
	if (argc > 4) {
		// should have sleepMin and sleepMax
		sleepMin = atof(argv[3]);
		sleepMax = atof(argv[4]);
	}
	if (sleepMin < 0 || sleepMax < 0 || sleepMax <= sleepMin) {
		fprintf(stderr, "Fatal: sleepMin/Max should satisfy 0 <= sleepMin < sleepMax\n");
		exit(0);
	}
	if (argc > 5) { randSeed = atoi(argv[5]); }
	if (argc > 6) {
		// also should have lock flag
		if (!strncmp(argv[6], "-lock", 5)) {
			strncpy(lock, "-lock", 6);
		}
		// if (strncmp(argv[6], "-nolock", 7)) {
		// 	fprintf(stderr, "Warning: last argument seemed odd; assuming -nolock.\n");
		// }
	}
	// DEBUG: print args
	// fprintf(stderr, "nBuffers=%i nWorkers=%i sleepMin=%f sleepMax=%f randSeed=%i lock=%s\n", nBuffers, nWorkers, sleepMin, sleepMax, randSeed, lock);

	// create zeroed out buffers array
	int *buffers = malloc(nBuffers * sizeof *buffers);
	for (i=0; i<nBuffers; i++) {
		buffers[i] = 0;
	}

	// create worker structs
	struct worker *workers = malloc(nWorkers * sizeof *workers);
	srand(randSeed);
	for (i=0; i<nWorkers; i++) {
		workers[i].nBuffers = nBuffers;
		workers[i].workerID = i+1;
		workers[i].sleepTime = sleepMin + (sleepMax-sleepMin)*rand()/RAND_MAX;
		workers[i].semID = -1;
		workers[i].mutexID = -1;
		workers[i].buffers = buffers;
		workers[i].nReadErrors = 0;
	}

	// create nWorkers threads, running the worker() function
	pthread_t *tids = malloc(nWorkers * sizeof *tids);
	for (i=0; i<nWorkers; i++) {
		pthread_create(&tids[i], 0, work, &workers[i]);
	}
	for (i=0; i<nWorkers; i++) {
		pthread_join(tids[i], 0);
	}

	// next up

	// free
	free(buffers);
	free(workers);
	free(tids);
}
