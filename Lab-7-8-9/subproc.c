#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "subproc_func.h"

int main(int argc, char* argv[])
{
	int callto = 20, maxSleep = 10;
	int seed = time(NULL);
	if(argc>=2) callto = atoi(argv[1]);
	if(argc>=3) maxSleep = atoi(argv[2]);
	if(argc>=4) seed = atoi(argv[3]);
	srand(seed);
	subproc_func(callto, maxSleep);

	return 0;
}
