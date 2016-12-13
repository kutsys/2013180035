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
	const char studentId[PIPE_BUF+1] = "2013180035";
	char myPid[PIPE_BUF+1], consumerPid[PIPE_BUF+1], studentName[PIPE_BUF+1];	
	sprintf(myPid, "%d", getpid());
	if(access(PRODUCER_FIFO, F_OK)==-1) {
		int res = mkfifo(PRODUCER_FIFO, 0666);
		if(res!=0) {
			printf("make fifo failed. exit program...\n");
			exit(EXIT_FAILURE);
		}
	}
	char cmdBuf[1024];
	int pipeId = -1;
	while(1) {
		scanf("%s", cmdBuf);
		if(strcmp(cmdBuf, "start")==0) {
			// open producer fifo for write
			pipeId = open(PRODUCER_FIFO, O_WRONLY);

			// write 1.myPid 2.studentId
			write(pipeId, myPid, PIPE_BUF);
			write(pipeId, studentId, PIPE_BUF);
			close(pipeId);

			// open consumer fifo for read
			pipeId = open(CONSUMER_FIFO, O_RDONLY);
 
			// read 1.consumerPid 2.studentName
			read(pipeId, consumerPid, PIPE_BUF);
			read(pipeId, studentName, PIPE_BUF);
			close(pipeId);
			printf("********** IPC-pipe **********\n");
			printf("[        ipc_producer        ]\n");
			printf(" ipc_producer_pid : %s\n student_id : %s\n -> ipc_consumer_pid : %s\n -> student_name : %s\n\n", myPid,  studentId, consumerPid, studentName);
		}
	}
	exit(EXIT_FAILURE);
}
