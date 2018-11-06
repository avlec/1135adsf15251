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

#define QUEUE_INITIALIZER (Queue) { .head = NULL, .tail = NULL, .length = 0 }

int q_push(Queue * queue, Customer customer);
Customer p_pop(Queue * queue);
Customer q_peek(Queue * queue);

typedef struct SynchronousQueue {
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutexattr;
	pthread_cond_t  cond;
	pthread_condattr_t condattr;
	
	pthread_mutex_t datamutex;
	pthread_mutexattr_t datamutexattr;
	Queue 			queue;
} SynchronousQueue;

void sq_init(SynchronousQueue * squeue);

int sq_push(SynchronousQueue * squeue, Customer customer);
Customer sq_pop(SynchronousQueue * squeue);
Customer sq_peek(SynchronousQueue * squeue);

void sq_lock(SynchronousQueue * squeue);
void sq_unlock(SynchronousQueue * squeue);
void sq_wake(SynchronousQueue * squeue);

#endif
