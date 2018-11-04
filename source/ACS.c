#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "ACS.h"
#include "Clerk.h"
#include "Queue.h"
#include "Lib.h"
#include "PriorityQueue.h"
#include "Input.h"

/* PThread Boys */

void * customer_thread(void * param);

Clerk clerk[4];

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
	unsigned int total_customers = read_input(&customer_list, argv[1]);

// Initalize the Priority Queue
	PriorityQueue pq = PRIORITY_QUEUE_INITIALIZER;

// Add customers to Priority Queue
	printf("Adding\n");
	for(unsigned int i = 0; i < total_customers; ++i) {
		print_customer(customer_list[i]);
		pq_push(&pq, customer_list[i]);
	}

	// Initialize Clerks
	for(int i=0;i<4;++i) clerk_init(clerk+i, i);

	struct timespec MAIN_SLEEP;
#ifdef __DEBUG
	MAIN_SLEEP.tv_sec = 1;
	MAIN_SLEEP.tv_nsec = 0;//100000000L;
#else
	MAIN_SLEEP.tv_sec = 0;
	MAIN_SLEEP.tv_nsec = 1000000;
#endif
	while(running) {
		if(nanosleep(&MAIN_SLEEP, NULL) < 0) {
			error_handler(ERROR_nanosleep);
			pthread_exit(NULL);
		}
		while(1) {
			// If the customers time hasn't arrived, done
			if(check_customer(pq_peek(&pq)))
				break;
			
			// Else take customer from queue
			Customer customer = pq_pop(&pq);
			
			// Add customer to proper queue.
			if(customer.type == 'B')
				sync_queue_push(&buisness_queue, customer);
			
			if(customer.type == 'E')
				sync_queue_push(&economy_queue, customer);
		}
	}
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
