makefile_exe : foo.o boo.o bar.o mtest.o
	gcc -g -o makefile_exe foo.o boo.o bar.o mtest.o

foo.o : foo.c
	gcc -g -c -o foo.o foo.c

boo.o : boo.c
	gcc -g -c -o boo.o boo.c

bar.o : bar.c
	gcc -g -c -o bar.o bar.c

mtest.o : mtest.c
	gcc -g -c -o mtest.o mtest.c

clean :
	rm *.o makefile_exe
