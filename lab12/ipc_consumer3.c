#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include "mymsg.h"

int main(int argc, char* argv[]) {
	const char* studentName = "Kim Ha Neul";
	char myPid[16];	
	sprintf(myPid, "%d", getpid());
	char producerPid[MYMSG_SIZE], studentId[MYMSG_SIZE];
	int msgKey = msgget(MYMSG_KEY, 0666 | IPC_CREAT);
	if(msgKey==-1) {
		perror("msgget failed\n");
		exit(EXIT_FAILURE);
	}
	MyMsg msgBuf; 
	while(1) {
		// receive 1.producerPid 2.studentId
		msgrcv(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long),
				PRODUCER_PUSHED, 0);
		strcpy(producerPid, msgBuf.msgBody);
		msgrcv(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long),
				PRODUCER_PUSHED, 0);
		strcpy(studentId, msgBuf.msgBody);
		printf("***** IPC-message queue ******\n");
		printf("[        ipc_consumer        ]\n");
		printf(" -> ipc_producer_pid : %s\n -> studnet_id : %s\n\n", producerPid
				, studentId);

		// send 1.myPid 2.studentName 
		msgBuf.msgType = CONSUMER_PUSHED;
		strcpy(msgBuf.msgBody, myPid);
		msgsnd(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long), 0);
		msgBuf.msgType = CONSUMER_PUSHED;
		strcpy(msgBuf.msgBody, studentName);
		msgsnd(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long), 0);
	}
	exit(EXIT_FAILURE);
}
