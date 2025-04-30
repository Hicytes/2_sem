CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c11
SRC = src/main.c src/geometry.c src/polygon.c
OUT = check

$(OUT): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(OUT) -lm

clean:
	rm -f $(OUT)
