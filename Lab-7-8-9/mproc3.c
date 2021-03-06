#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "subproc_func.h"

#define EXECTO 10

int testFunctCalled = 0;
pthread_mutex_t tfcMutex;
void* subprocSync(void* arg) {
	const int callto = 20, maxSleep=10;
        int i=0;
	for(i=0; i<callto; ++i) {
		test_funct(i+1);
		pthread_mutex_lock(&tfcMutex);
		++testFunctCalled;
		pthread_mutex_unlock(&tfcMutex);
		while(testFunctCalled/EXECTO <= i)
			sleep(0);
		if(i+1!=callto)
			sleep(1+(rand()%maxSleep));
	}
	return 0;
}

int main(int argc, char* argv[]) {
	printf("Lab-9, 2013180035 Kim Ha Neul\n");
	pthread_mutex_init(&tfcMutex, NULL);
	pthread_t threads[EXECTO];
        int i=0;
	for(i=0; i<EXECTO; ++i) {
		int res = pthread_create(&threads[i], NULL, subprocSync, NULL);
		if(res!=0) {
			printf("thread create failed. exit program...\n");
			exit(EXIT_FAILURE);
		}
	}
        int ii=0;
	for(ii=0; ii<EXECTO; ++ii) {
		int res = pthread_join(threads[ii], NULL);
		if(res!=0) {
			printf("thread join failed. exit program...\n");
			exit(EXIT_FAILURE);
		}
	}
	pthread_mutex_destroy(&tfcMutex);
	printf("Finished Successfully\n");

	exit(0);
}
