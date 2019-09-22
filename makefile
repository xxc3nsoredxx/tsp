CC = gcc
CFLAGS = -c -Wall -Wextra -std=c89 --pedantic-errors
SRC = src
BIN = bin
LIB = lib
INC = inc
OBJS = $(BIN)/main.o
LFLAGS = -L$(LIB) -lfbg
IFLAGS = -I$(INC)

all: $(BIN)/tsp

$(BIN)/tsp: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(BIN)/tsp

$(BIN)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $(IFLAGS) $(SRC)/main.c -o $(BIN)/main.o
