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

pthread_t clerk1;
pthread_mutex_t clerk1_m;
pthread_cond_t clerk1_c;

pthread_t clerk2;
pthread_mutex_t clerk2_m;
pthread_cond_t clerk2_c;

pthread_t clerk3;
pthread_mutex_t clerk3_m;
pthread_cond_t clerk3_c;

pthread_t clerk4;
pthread_mutex_t clerk4_m;
pthread_cond_t clerk4_c;

/* Queues and Protective Structures */

pthread_mutex_t bsns_queue_mutex;
pthread_cond_t bsns_queue_cond;
Queue bsns_c_queue;

pthread_mutex_t econ_queue_mutex;
pthread_cond_t econ_queue_cond;
Queue econ_c_queue;

/* Reading Input (Easy Money) */


int main(int argc, char ** argv) {
	int running = 1;


	if(argc != 2) {
		printf("Expected usage: ./ACS <text file>\n");
		exit(1);
	}
	
	Customer * customer_list = NULL;
	int total_customers;

	{ // Parse Input
		FILE * in = fopen(argv[1], "r");
		total_customers = fget_customers(in, &customer_list);
		fclose(in);
	}

	PriorityQueue pq = PRIORITY_QUEUE_INITIALIZER;
	
	printf("Adding\n");
	for(int i = 0; i < total_customers; ++i) {
		print_customer(customer_list[i]);
		pq_push(&pq, customer_list[i]);
	}
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

void * clerk(void * param) {
	printf("Press F to pay respects");
	return NULL;
}

void * customer(void * param) {
	printf("Press F to pay respects");
	return NULL;
}
