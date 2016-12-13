#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include "mymsg.h"

// Lab-12
int main(int argc, char* argv[]) {
	const char* studentId = "2013180035";
	char myPid[16];	
	sprintf(myPid, "%d", getpid());
	char consumerPid[MYMSG_SIZE], studentName[MYMSG_SIZE];
	int msgKey = msgget(MYMSG_KEY, 0666 | IPC_CREAT);
	if(msgKey==-1) {
		perror("msgget failed\n");
		exit(EXIT_FAILURE);
	}
	MyMsg msgBuf; 
	// clear message queue
	while(msgrcv(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long),
				0, IPC_NOWAIT)!=-1);
	char cmdBuf[1024];
	while(1) {
		scanf("%s", cmdBuf);
		if(strcmp(cmdBuf, "start")==0) {
			// write 1.myPid 2.studentId 
			msgBuf.msgType = PRODUCER_PUSHED;
			strcpy(msgBuf.msgBody, myPid);
			msgsnd(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long), 0);
			msgBuf.msgType = PRODUCER_PUSHED;
			strcpy(msgBuf.msgBody, studentId);
			msgsnd(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long), 0);

			// read 1.consumerPid 2.studentName
			msgrcv(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long),
					CONSUMER_PUSHED, 0);
			strcpy(consumerPid, msgBuf.msgBody);
			msgrcv(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long),
					CONSUMER_PUSHED, 0);
			strcpy(studentName, msgBuf.msgBody);
			printf("***** IPC-message queue ******\n");
			printf("[        ipc_producer        ]\n");
			printf(" ipc_producer_pid : %s\n student_id : %s\n -> ipc_consumer_pid : %s\n -> student_name : %s\n\n", myPid,  studentId, consumerPid, studentName);
		}
	}
	exit(EXIT_FAILURE);
}
