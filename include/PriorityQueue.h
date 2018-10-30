#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Datatypes.h"

typedef struct PQNode {
	struct PQNode * next;
	struct Customer customer;
} PQNode;

typedef struct PriorityQueue {
	struct PQNode * head;
	unsigned int length;
} PriorityQueue;

#define PRIORITY_QUEUE_INITIALIZER { .head = NULL, .length = 0 }

void pq_push(PriorityQueue * pqueue, Customer customer);
Customer pq_pop(PriorityQueue * pqueue); 
Customer pq_peek(PriorityQueue * pqueue);

#endif
