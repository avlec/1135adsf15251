#include <stdlib.h>
#include <stdio.h>

#include "Queue.h"
#include "Lib.h"

int q_push(Queue * queue, Customer customer) {
	QNode * new_node = (QNode *) malloc(sizeof(QNode));
	if(new_node == NULL) {
		error_handler(ERROR_malloc);
		exit(1);
	}

	if(queue->head == NULL) {
		queue->head = queue->tail = new_node;
	} else {
		queue->tail->next = new_node;
	}
	new_node->customer = customer;
	return ++queue->length;
}

Customer q_pop(Queue * queue) {
	Customer customer = CUSTOMER_INITIALIZER;
	if(queue->head != NULL) {
		customer = queue->head->customer;
		QNode * temp = queue->head;
		queue->head = queue->head->next;
		free(temp);
		queue->length--;
	}
	return customer;
}

Customer q_peek(Queue * queue) {
	Customer customer = CUSTOMER_INITIALIZER;
	if(queue->head != NULL)
		customer = queue->head->customer;
	return customer;
}

int sync_queue_push(SynchronousQueue * squeue, Customer customer) {
	pthread_mutex_lock(&squeue->mutex);				//   Lock
	int length = q_push(&squeue->queue, customer);	// Modify
	pthread_mutex_unlock(&squeue->mutex);			// UnLock
	print_customer(customer);
	return length;
}

Customer sync_queue_pop(SynchronousQueue * squeue) {
	Customer customer = CUSTOMER_INITIALIZER;
	pthread_mutex_lock(&squeue->mutex);		//   Lock
	customer = q_pop(&squeue->queue);		// Modify
	pthread_mutex_unlock(&squeue->mutex);	// Unlock
	return customer;
}

unsigned int sync_queue_peek(SynchronousQueue * squeue) {
	return squeue->queue.head->customer.uid;
}
