CC = gcc
CFLAGS = -Wall -g -I./include
SRC_DIR = src
OBJ_DIR = obj
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/random.o $(OBJ_DIR)/geometry.o $(OBJ_DIR)/welzl.o

# Основная цель
all: min_enclosing_circle

min_enclosing_circle: $(OBJ)
	$(CC) $(OBJ) -o min_enclosing_circle -lm

# Компиляция main.c
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c include/random.h include/geometry.h include/welzl.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

# Компиляция random.c
$(OBJ_DIR)/random.o: $(SRC_DIR)/random.c include/random.h include/geometry.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/random.c -o $(OBJ_DIR)/random.o

# Компиляция geometry.c
$(OBJ_DIR)/geometry.o: $(SRC_DIR)/geometry.c include/geometry.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/geometry.c -o $(OBJ_DIR)/geometry.o

# Компиляция welzl.c
$(OBJ_DIR)/welzl.o: $(SRC_DIR)/welzl.c include/welzl.h include/random.h include/geometry.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/welzl.c -o $(OBJ_DIR)/welzl.o

# Очистка
clean:
	rm -rf $(OBJ_DIR) min_enclosing_circle

