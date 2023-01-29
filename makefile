CC = g++
CFLAGS = -std=c++11 -Wall -O2
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

all: main clean

main: main.o omega.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/main.out $(SRC_DIR)/main.o $(SRC_DIR)/omega.o

main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $(SRC_DIR)/main.cpp -o $(SRC_DIR)/main.o

omega.o: $(SRC_DIR)/omega.cpp $(INC_DIR)/omega.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $(SRC_DIR)/omega.cpp -o $(SRC_DIR)/omega.o

clean: 
	rm -f $(SRC_DIR)/*.o

install:
	cp $(BIN_DIR)/main.out /usr/local/bin