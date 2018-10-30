CC=gcc
CFLAGS=-g -Wall -Werror -ansi -std=c99
SRC=../source/
HDR=../header/
INCLUDE_DIR=-I../header/
OBJECT_LIST=Queue.o PriorityQueue.o Datatypes.o Lib.o


ACS: $(SRC)ACS.c $(HDR)ACS.h Queue.o PriorityQueue.o
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(OBJECT_LIST) ../source/ACS.c -o ACS

Queue.o: $(SRC)Queue.c $(HDR)Queue.h Datatypes.o Lib.o
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) ../source/Queue.c -o Queue.o

PriorityQueue.o: $(SRC)PriorityQueue.c $(HDR)PriorityQueue.h Datatypes.o Lib.o
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) ../source/PriorityQueue.c -o PriorityQueue.o

Datatypes.o: $(SRC)Datatypes.c $(HDR)Datatypes.h
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) ../source/Datatypes.c -o Datatypes.o

Lib.o: $(SRC)Lib.c $(HDR)Lib.h
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) ../source/Lib.c -o Lib.o

