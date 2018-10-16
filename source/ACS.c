#include <stdlib.h>
#include <stdio.h>

/*
 * @short
 * Data structure for data structure usage.
 * @detailed
 * t1
 * t2
 * ...
 */
typedef struct data_s {
	
} data_s;


/*
 * Priority Queue Implimentation
 */
typedef struct pq_node {
	data_s data;
	struct pq_node * left_child;
	struct pq_node * right_child;
} pq_node;

typedef struct PriorityQueue {
	pq_node * root;
	void * compare_function;
	size_t size;
} PriorityQueue;

void pqueue_psh(PriorityQueue * pq, data_s data);
data_s pqueue_pop(PriorityQueue * pq);
data_s pqueue_peek(PriorityQueue * pq);


void pqueue_psh(PriorityQueue * pq, data_s data) {
	// Complex.	
}

data_s pqueue_pop(PriorityQueue * pq) {
	data_s data;
	// Complex.
	return data;
}

data_s pqueue_peek(PriorityQueue * pq) {
	data_s data;
	// easy
	return data;
}

/*
 *	Queue Implimentation
 */
typedef struct q_node {
	data_s data;
	struct q_node * next;
	struct q_node * prev;
} q_node;

typedef struct Queue {
	size_t q_size;
	q_node * head;
	q_node * tail;
} Queue;

void queue_psh(Queue * queue, data_s data);
data_s queue_pop(Queue * queue);
data_s queue_peek(Queue * queue);

void queue_psh(Queue * queue, data_s data) {
	q_node * new_qnode = (q_node *) malloc(sizeof(q_node));
	if(queue->head == NULL) {
		queue->head = 
}

data_s queue_pop(Queue * queue) {
	data_s data; //TODO empty initialize
	
	if(queue->head == NULL) {
		return data;
	}

	data = queue->head.data;
	queue->head = queue->head.next;

	return data;
}

data_s queue_peek(Queue * queue) {
	if(queue->head == NULL) {
		data_s data; //TODO empty intialize
		return data;
	}
	return queue->head.data;
}

int main(int argc, char ** argv) {
	int running = 1;
	
	{ // Parse Input
	}

	while(running) {
		
	}
}
