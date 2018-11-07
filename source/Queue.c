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

void sq_init(SynchronousQueue * squeue) {
	if(pthread_mutexattr_init(&squeue->datamutexattr)) {
		error_handler(ERROR_pthread_mutexattr_init);
		exit(1);
	}
	if(pthread_mutex_init(&squeue->datamutex, &squeue->datamutexattr)) {
		error_handler(ERROR_pthread_mutex_init);
		exit(1);
	}
	squeue->queue = QUEUE_INITIALIZER;
}

int sq_push(SynchronousQueue * squeue, Customer customer) {
	if(pthread_mutex_lock(&squeue->datamutex)) {
		error_handler(ERROR_pthread_mutex_lock);
		exit(1);
	}
	int length = q_push(&squeue->queue, customer);	// Modify
	if(pthread_mutex_unlock(&squeue->datamutex)) {
		error_handler(ERROR_pthread_mutex_unlock);
		exit(1);
	}
	return length;
}

Customer sq_pop(SynchronousQueue * squeue) {
	Customer customer = CUSTOMER_INITIALIZER;
	if(pthread_mutex_lock(&squeue->datamutex)) {
		error_handler(ERROR_pthread_mutex_lock);
		exit(1);
	}
	customer = q_pop(&squeue->queue);	// Modify
	if(pthread_mutex_unlock(&squeue->datamutex)) {
		error_handler(ERROR_pthread_mutex_unlock);
		exit(1);
	}
	return customer;
}


Customer sq_peek(SynchronousQueue * squeue) {
	Customer customer = CUSTOMER_INITIALIZER;
	if(pthread_mutex_lock(&squeue->datamutex)) {
		error_handler(ERROR_pthread_mutex_lock);
		exit(1);
	}
	customer = q_peek(&squeue->queue);	// Look
	if(pthread_mutex_unlock(&squeue->datamutex)) {
		error_handler(ERROR_pthread_mutex_unlock);
		exit(1);
	}
	return customer;
}
