#include <stdlib.h>

#include "Queue.h"
#include "Lib.h"

void q_push(Queue * queue, Customer customer) {
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
}

Customer p_pop(Queue * queue) {
	Customer customer = CUSTOMER_INITIALIZER;
	if(queue->head != NULL) {
		customer = queue->head->customer;
		QNode * temp = queue->head;
		queue->head = queue->head->next;
		free(temp);
	}
	return customer;
}

Customer q_peek(Queue * queue) {
	Customer customer = CUSTOMER_INITIALIZER;
	if(queue->head != NULL)
		customer = queue->head->customer;
	return customer;
}

void sync_queue_push(SynchronousQueue * squeue, Customer customer) {
	return;
}

Customer sync_queue_pop(SynchronousQueue * squeue) {
	Customer customer = CUSTOMER_INITIALIZER;
	return customer;
}
