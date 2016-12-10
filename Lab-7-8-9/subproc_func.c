#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int test_funct(int count) {
	static int calledCount = 0;
	time_t currentTime;
	time(&currentTime);
	++calledCount;
	printf("test_funct - pid:%d, called(prc):%d, count(func):%d, time:%s",
			getpid(), calledCount, count, ctime(&currentTime));
	return calledCount;
}

void subproc_func(int callto, int maxSleep)
{
	for(int i=0; i<callto; ++i) {
		test_funct(i+1);
		if(i+1!=callto) {
			int s = (rand()%maxSleep)+1;
			sleep(s);
		}
	}
}
