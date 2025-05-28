CC = gcc
CFLAGS = -O2 -Wall -std=c99

all: inverse

inverse: main.o matrix.o
	$(CC) $(CFLAGS) -o inverse main.o matrix.o

main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

clean:
	rm -f *.o inverse
