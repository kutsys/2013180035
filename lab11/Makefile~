
all : ipc_producer ipc_consumer

ipc_producer : ipc_producer.c
	gcc -Wall -o ipc_producer ipc_producer.c

ipc_consumer : ipc_consumer.c
	gcc -Wall -o ipc_consumer ipc_consumer.c

clean :
	rm ipc_producer ipc_consumer
