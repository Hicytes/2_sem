CC = gcc
CFLAGS = -O2 -Wall -std=c99
LDLIBS = -lm  

all: inverse

inverse: main.o matrix.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) 

main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c $<

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o inverse
