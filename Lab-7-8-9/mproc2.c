#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "subproc_func.h"

#define EXECTO 10

void* subprocThread(void* arg) {
	subproc_func(20,10);
	return NULL;
}

int main(int argc, char* argv[]) {
	printf("Lab-8, 2013180035 Kim Ha Neul\n");
	srand(time(NULL));
	pthread_t threads[EXECTO];
        int i=0;
	for(i=0; i<EXECTO; ++i) {
		int res = pthread_create(&threads[i], NULL, subprocThread, NULL);
		if(res!=0) {
			printf("thread create failed. exit program...\n");
			exit(EXIT_FAILURE);
		}
	}
        int ii=0;
	for(ii=0; ii<EXECTO; ++ii) {
		int res = pthread_join(threads[i], NULL);
		if(res!=0) {
			printf("Thread join failed. exit program...\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("Finished (thread)\n");
	exit(0);
}
