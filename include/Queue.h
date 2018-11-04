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

typedef struct SynchronousQueue {
	pthread_mutex_t mutex;
	pthread_cond_t  convar;
	Queue 			queue;
} SynchronousQueue;

void sync_queue_push(SynchronousQueue * squeue, Customer customer);
Customer sync_queue_pop(SynchronousQueue * squeue);

#endif
