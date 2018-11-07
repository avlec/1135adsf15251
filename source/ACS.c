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
	.tv_nsec = 100000000
#endif
};

unsigned int ms_time = 0;

pthread_cond_t cond;
pthread_mutex_t mutex;
Clerk clerk[4];

SynchronousQueue buisness_queue;
SynchronousQueue economy_queue;

waiting_times times;

int no_more_customers = 0;

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

// Initialize waiting times arrays
	init_waiting_times(&times, total_customers);

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
#ifdef __DEBUG
		fprintf(stderr, "Passed ms %d\n", ms_time);
#endif
		if(nanosleep(&MAIN_SLEEP, NULL) < 0) {
			error_handler(ERROR_nanosleep);
			exit(EXIT_FAILURE);
		}
		++ms_time;
	}
#ifdef __DEBUG
	printf("All customers have arrived for the day.\n");
#endif

	if(nanosleep(&MAIN_SLEEP, NULL) < 0) {
		error_handler(ERROR_nanosleep);
		exit(EXIT_FAILURE);
	}
	++ms_time;

	no_more_customers = 1;
	
	while((clerk[0].cid + clerk[1].cid + clerk[2].cid + clerk[3].cid) != -4) {
		if(nanosleep(&MAIN_SLEEP, NULL) < 0) {
			error_handler(ERROR_nanosleep);
			exit(EXIT_FAILURE);
		}
		++ms_time;
	}
	for(int i = 0; i < 4; ++i)
		if(pthread_join(clerk[i].thread, NULL)) {
			error_handler(ERROR_pthread_join);
			exit(EXIT_FAILURE);
		}

	printf("The average waiting time for all customers "
		   "in the system is: %.2f seconds.  \n", calc_avg_wait_all(&times));
	printf("The average waiting time for all customers "
		   "in the buisness class is: %.2f seconds.  \n", calc_avg_wait_buisness(&times));
	printf("The average waiting time for all customers "
		   "in the economy class is: %.2f seconds.  \n", calc_avg_wait_economy(&times));
	
	exit(EXIT_SUCCESS);
}


