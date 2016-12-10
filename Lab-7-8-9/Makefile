
all : mproc1 mproc2 mproc3

mproc3 : mproc3.c subproc_func.o subproc_func.h
	gcc -Wall -o mproc3 mproc3.c subproc_func.o -lpthread

mproc2 : mproc2.c subproc_func.o subproc_func.h
	gcc -Wall -o mproc2 mproc2.c subproc_func.o -lpthread

mproc1 : mproc1.c subproc
	gcc -Wall -o mproc1 mproc1.c

subproc : subproc.c subproc_func.o subproc_func.h
	gcc -Wall -o subproc subproc.c subproc_func.o

subproc_func.o : subproc_func.c
	gcc -Wall -c -o subproc_func.o subproc_func.c
