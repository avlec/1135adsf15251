#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "ACS.h"
#include "Queue.h"
#include "Lib.h"
#include "PriorityQueue.h"
#include "Input.h"

/* PThread Boys */

void * clerk_thread(void * param);
void * customer_thread(void * param);

typedef struct Clerk {
	pthread_t 		thread;
	pthread_attr_t 	attr;
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutex_attr;
	pthread_cond_t 	cond;
	pthread_condattr_t cond_attr;
} Clerk;

void clerk_init(Clerk * clerk, unsigned int clerk_id);

void clerk_init(Clerk * clerk, unsigned int clerk_id) {
	if(pthread_mutexattr_init(&clerk->mutex_attr)) {
		error_handler(ERROR_pthread_mutexattr_init);
		exit(1);
	}
	if(pthread_mutex_init(&clerk->mutex, &clerk->mutex_attr)) {
		error_handler(ERROR_pthread_mutex_init);
		exit(1);
	}
	if(pthread_condattr_init(&clerk->cond_attr)) {
		error_handler(ERROR_pthread_condattr_init);
		exit(1);
	}
	if(pthread_cond_init(&clerk->cond, &clerk->cond_attr)) {
		error_handler(ERROR_pthread_cond_init);
		exit(1);
	}
	if(pthread_attr_init(&clerk->attr)) {
		error_handler(ERROR_pthread_attr_init);
		exit(1);
	}
	void * args = malloc(sizeof(unsigned int));
	if(args == NULL) {
		error_handler(ERROR_malloc);
		exit(1);
	}
	memcpy(args, &clerk_id, sizeof(unsigned int));
	if(pthread_create(&clerk->thread, &clerk->attr, clerk_thread, args)) {
		error_handler(ERROR_pthread_create);
		exit(1);
	}
}

Clerk clerk[4];

/* Synchronous (Thread Safe) Queues */

typedef struct SynchronousQueue {
	pthread_mutex_t mutex;
	pthread_cond_t  convar;
	Queue 			queue;
} SynchronousQueue;

void sync_queue_push(SynchronousQueue * squeue, Customer customer);
Customer sync_queue_pop(SynchronousQueue * squeue);

void sync_queue_push(SynchronousQueue * squeue, Customer customer) {
	return;
}
Customer sync_queue_pop(SynchronousQueue * squeue) {
	Customer customer = CUSTOMER_INITIALIZER;
	return customer;
}

SynchronousQueue buisness_queue;
SynchronousQueue economy_queue;



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
	{	
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

	// Initialize Clerks
	for(int i=0;i<4;++i) clerk_init(clerk+i, i);

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
void * clerk_thread(void * param) {
	unsigned int clerk_id = *((unsigned int *)param);	

	struct timespec CLERK_SLEEP;
#ifdef __DEBUG
	CLERK_SLEEP.tv_sec = 1;
	CLERK_SLEEP.tv_nsec = 0;//100000000L;
#else
	CLERK_SLEEP.tv_sec = 0;
	CLERK_SLEEP.tv_nsec = 1000000;
#endif

	while(1) {
		printf("Clerk %d ready, and waiting to serve a customer.\n", clerk_id);
		Customer customer;
		while(1) {
			// Check queues every 1ms
			
			if(nanosleep(&CLERK_SLEEP, NULL) < 0) {
				error_handler(ERROR_nanosleep);
				pthread_exit(NULL);
			}

			customer = sync_queue_pop(&buisness_queue);	
			if(!check_customer(customer)) // buisness class customer found
				break;

			customer = sync_queue_pop(&economy_queue);
			if(!check_customer(customer)) // economy class customer found
				break;
			fprintf(stderr, "F\n");
		}
	/*	
		pthread_mutex_lock(&clerk[clerk_id].mutex);
		while(i_have_customer)
			pthread_cond_wait(&clerk[clerk_id].cond, &clerk[clerk_id].lock);
	*/
		// start customer thread
		// wait on my condition variable
		// wake up and reloop	
	}
	pthread_exit(0);
}

/*
 *
 *
 */
void * customer_thread(void * param) {
	printf("Waiting to be served!\n");
	// sleep
	//
	pthread_exit(0);
}
