CC = gcc
CFLAGS = -c -g -Wall
IFLAGS = -I.

main: main.o cpu1.o cpu2.o readmem.o
	$(CC) main.o cpu1.o cpu2.o readmem.o -o main

cpu1.o: cpu1.c headers.h sharedmem.h 
	$(CC) $(IFLAGS) $(CFLAGS) cpu1.c -o cpu1.o

cpu2.o: cpu2.c headers.h sharedmem.h 
	$(CC) $(IFLAGS) $(CFLAGS) cpu2.c -o cpu2.o

readmem.o: readmem.c headers.h sharedmem.h 
	$(CC) $(IFLAGS) $(CFLAGS) readmem.c -o readmem.o

clean: 
			rm -f main
			rm -f *.o
