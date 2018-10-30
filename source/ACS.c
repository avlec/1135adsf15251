#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>

//#include "avlec.h"
#include "ACS.h"
#include "Queue.h"
#include "Lib.h"
#include "PriorityQueue.h"
#include "Input.h"

/* PThread Boys */

void * clerk(void * param);
void * customer(void * param);

typedef struct Clerk {
	pthread_t 		thread;
	pthread_mutex_t mutex;
	pthread_cond_t 	convar;
} Clerk;

Clerk clerk1;
Clerk clerk2;
Clerk clerk3;
Clerk clerk4;

/* Synchronous (Thread Safe) Queues */

typedef struct SynchronousQueue {
	pthread_mutex_t mutex;
	pthread_cond_t  convar;
	Queue 			queue;
} SynchronousQueue;

/* Thread safe wrapper functions */
void sq_push(SynchronousQueue * squeue, Customer customer);
Customer sq_pop(SynchronousQueue * squeue);
Customer sq_peek(SynchronousQueue * squeue);

void sq_push(SynchronousQueue * squeue, Customer customer) {
	return;
}

Customer sq_pop(SynchronousQueue * squeue) {
	Customer customer;

	return customer;
}

Customer sq_peek(SynchronousQueue * squeue) {
	Customer customer;

	return customer;
}


SynchronousQueue buisness;
SynchronousQueue economy;

int main(int argc, char ** argv) {
	int running = 1;

// Check for appropriate commandline arguments.
	if(argc != 2) {
		printf("Expected usage: ./ACS <text file>\n");
		exit(1);
	}

// Setup Holding structure for customers	
	Customer * customer_list = NULL;
	int total_customers;
// Parse Customers from Input File and place  into customer_list
	}	
	FILE * in = fopen(argv[1], "r");
	total_customers = fget_customers(in, &customer_list);
	fclose(in);
	}

// Initalize the Priority Queue
	PriorityQueue pq = PRIORITY_QUEUE_INITIALIZER;

// Add customers to Priority Queue
	printf("Adding\n");
	for(int i = 0; i < total_customers; ++i) {
		print_customer(customer_list[i]);
		pq_push(&pq, customer_list[i]);
	}

// Remove customers from Priority Queue to test ordering.
	printf("Now removing\n");
	for(int i = 0; i < total_customers; ++i) {
		print_customer(pq_pop(&pq));
	}


	while(running) {
		// while top customers arrival time has passed
		// 		remove customer from pq
		// 		add to proper q
		// end
	}
}

/*
 *
 *
 */
void * clerk(void * param) {
	printf("Press F to pay respects");
	return NULL;
}

/*
 *
 *
 */
void * customer(void * param) {
	printf("Press F to pay respects");
	return NULL;
}
