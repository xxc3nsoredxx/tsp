CC = gcc
CFLAGS = -c -Wall -Wextra -std=c89 --pedantic-errors
SRC = src
BIN = bin
LIB = lib
INC = inc
OBJS = $(BIN)/main.o $(BIN)/parray.o $(BIN)/hull.o
LFLAGS = -L$(LIB) -lfbg -lm
IFLAGS = -I$(INC)

all: $(BIN)/tsp

$(BIN)/tsp: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(BIN)/tsp

$(BIN)/main.o: $(SRC)/main.c $(INC)/parray.h $(INC)/hull.h
	$(CC) $(CFLAGS) $(IFLAGS) $(SRC)/main.c -o $(BIN)/main.o

$(BIN)/parray.o: $(SRC)/parray.c $(INC)/parray.h
	$(CC) $(CFLAGS) $(IFLAGS) $(SRC)/parray.c -o $(BIN)/parray.o

$(BIN)/hull.o: $(SRC)/hull.c $(INC)/hull.h $(INC)/parray.h
	$(CC) $(CFLAGS) $(IFLAGS) $(SRC)/hull.c -o $(BIN)/hull.o
