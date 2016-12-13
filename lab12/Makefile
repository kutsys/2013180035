
all : ipc_producer3 ipc_consumer3

ipc_producer3 : ipc_producer3.c mymsg.h
	gcc -Wall -o ipc_producer3 ipc_producer3.c

ipc_consumer3 : ipc_consumer3.c mymsg.h
	gcc -Wall -o ipc_consumer3 ipc_consumer3.c

clean : 
	rm ipc_producer3 ipc_consumer3
