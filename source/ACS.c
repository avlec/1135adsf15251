#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "ACS.h"
#include "Clerk.h"
#include "Customer.h"
#include "Queue.h"
#include "Lib.h"
#include "PriorityQueue.h"
#include "Input.h"

struct timespec MAIN_SLEEP = {
#ifdef __DEBUG
	.tv_sec = 1,
	.tv_nsec = 0
#else
	.tv_sec = 0,
	.tv_nsec = 1000000
#endif
};

unsigned int ms_time = 0;

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

// Setup Synchronous Queues
	sq_init(&buisness_queue);
	sq_init(&economy_queue);

// Setup Holding structure for customers	
	Customer * customer_list = NULL;
	unsigned int total_customers = read_input(&customer_list, argv[1]);

// Initalize the Priority Queue
	PriorityQueue pq = PRIORITY_QUEUE_INITIALIZER;

// Add customers to Priority Queue
	for(unsigned int i = 0; i < total_customers; ++i) {
		pq_push(&pq, customer_list[i]);
	}

	// Initialize Clerks
	for(int i=0;i<4;++i) clerk_init(clerk+i, i);


	while(running) {
		while(1) {
			Customer customer = pq_peek(&pq);
			// If no more customers done
			if(check_customer(customer)) {
				running = 0;
				break;
			}

			// If the customers time hasn't arrived, done
			if(ms_time < customer.arrival_time)
				break;

			// Else take customer from queue
			pq_pop(&pq);

			customer_init(customer);
		}
		fprintf(stderr, "Passed ms %d\n", ms_time);
		if(nanosleep(&MAIN_SLEEP, NULL) < 0) {
			error_handler(ERROR_nanosleep);
			pthread_exit(NULL);
		}
		++ms_time;
	}
	printf("All customers have arrived for the day.\n");
}


