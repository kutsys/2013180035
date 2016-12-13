// Lab-12

#define MYMSG_KEY 12188
#define MYMSG_SIZE 64

#define PRODUCER_PUSHED 1
#define CONSUMER_PUSHED 2

typedef struct _MyMsg {
	long msgType;
	char msgBody[MYMSG_SIZE];
} MyMsg;
