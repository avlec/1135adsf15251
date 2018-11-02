#include <stdlib.h>

#include "PriorityQueue.h"
#include "Lib.h"

/* Linked List Priority Queue Implimentation fot this Project
 *
 *	O(n) insertion
 *	O(1) peek/pop
 *
 * */


void pq_push(PriorityQueue * pqueue, Customer customer) {
	PQNode * new_node = (PQNode *) malloc(sizeof(PQNode));
	if(new_node == NULL) {
		error_handler(ERROR_malloc);
		exit(1);
	}
	new_node->customer = customer;
	new_node->next = NULL;

	if(pqueue->head == NULL) {
		pqueue->head = new_node;
		return;
	}

	// If it's the lowest priority, ya done boy
	if(pqueue->head->customer.arrival_time > customer.arrival_time) {
		new_node->next = pqueue->head;
		pqueue->head = new_node;
		return;
	}
	
	// Else ya gotta get it
	PQNode * temp = pqueue->head;
	while((temp->next != NULL) && (temp->next->customer.arrival_time < customer.arrival_time)) {
		temp = temp->next;
	}
	new_node->next = temp->next;
	temp->next = new_node;
}

Customer pq_pop(PriorityQueue * pqueue) {
	Customer customer = CUSTOMER_INITIALIZER;
	if(pqueue->head == NULL) // invalid remove
		return customer;

	customer = pqueue->head->customer; // Get return val
	PQNode * temp = pqueue->head; // Keep copy to free
	pqueue->head = pqueue->head->next; // Update pq
	free(temp); // Free old head
	return customer;
}

Customer pq_peek(PriorityQueue * pqueue) {
	Customer customer = CUSTOMER_INITIALIZER;
	if(pqueue->head == NULL) // invalid peek
		return customer;
	return pqueue->head->customer;
}
