CC=gcc
CFLAGS=-g -Wall -Werror -ansi -std=c99 -pthread #-lrt #-D__DEBUG
SRC=../source/
HDR=../include/
INCLUDE_DIR=-I../include/
OBJECT_LIST=Clerk.o Customer.o Queue.o PriorityQueue.o Input.o Datatypes.o Lib.o


ACS: $(SRC)ACS.c $(HDR)ACS.h $(OBJECT_LIST)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(OBJECT_LIST) $(SRC)ACS.c -o ACS

Clerk.o: $(SRC)Clerk.c $(HDR)Clerk.h Queue.o Datatypes.o Lib.o
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) $(SRC)Clerk.c -o Clerk.o

Customer.o: $(SRC)Customer.c $(HDR)Customer.h Queue.o Datatypes.o Lib.o
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) $(SRC)Customer.c -o Customer.o

Queue.o: $(SRC)Queue.c $(HDR)Queue.h Datatypes.o Lib.o
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) $(SRC)Queue.c -o Queue.o

PriorityQueue.o: $(SRC)PriorityQueue.c $(HDR)PriorityQueue.h Datatypes.o Lib.o
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) $(SRC)PriorityQueue.c -o PriorityQueue.o

Input.o: $(SRC)Input.c $(HDR)Input.h
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) $(SRC)Input.c -o Input.o

Datatypes.o: $(SRC)Datatypes.c $(HDR)Datatypes.h
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) $(SRC)Datatypes.c -o Datatypes.o

Lib.o: $(SRC)Lib.c $(HDR)Lib.h
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) $(SRC)Lib.c -o Lib.o

