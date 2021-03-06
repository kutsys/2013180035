#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#define PRODUCER_FIFO "/tmp/prdc_fifo"
#define CONSUMER_FIFO "/tmp/csm_fifo"

int main(int argc, char* argv[]) {
	const char studentName[PIPE_BUF+1] = "Kim Ha Neul";
	char myPid[PIPE_BUF+1], producerPid[PIPE_BUF+1], studentId[PIPE_BUF+1];	
	sprintf(myPid, "%d", getpid());
	if(access(CONSUMER_FIFO, F_OK)==-1) {
		int res = mkfifo(CONSUMER_FIFO, 0666);
		if(res!=0) {
			printf("make fifo failed. exit program...\n");
			exit(EXIT_FAILURE);
		}
	}
	int pipeId = -1;
	while(1) {
		// open producer fifo for read
		pipeId = open(PRODUCER_FIFO, O_RDONLY);

		// read 1.myPid 2.studentId
		read(pipeId, producerPid, PIPE_BUF);
		read(pipeId, studentId, PIPE_BUF);
		close(pipeId);
		printf("********** IPC-pipe **********\n");
		printf("[        ipc_producer        ]\n");
		printf(" -> ipc_producer_pid : %s\n -> studnet_id : %s\n\n", producerPid
				, studentId);

		// open consumer fifo for write
		pipeId = open(CONSUMER_FIFO, O_WRONLY);

		// write 1.consumerPid 2.studentName
		write(pipeId, myPid, PIPE_BUF);
		write(pipeId, studentName, PIPE_BUF);
		close(pipeId);
	}
	exit(EXIT_FAILURE);
}
