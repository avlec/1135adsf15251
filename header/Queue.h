#ifndef QUEUE_H
#define QUEUE_H

#include "Datatypes.h"

/* Queue Implimenation for this Project 
 *
 *	O(1) insertion/pop/peek
 *
 * */

typedef struct QNode {
	struct QNode * next;
	struct QNode * prev;
	struct Customer customer;
} QNode;

typedef struct Queue {
	struct QNode * head;
	struct QNode * tail;
	unsigned int length;
} Queue;

#define QUEUE_INITIALIER { .head = NULL, .tail = NULL, .length = 0 }

void q_push(Queue * queue, Customer customer);
Customer p_pop(Queue * queue);
Customer q_peek(Queue * queue);

#endif
