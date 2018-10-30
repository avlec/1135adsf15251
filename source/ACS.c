#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>

//#include "avlec.h"
#include "ACS.h"
#include "Queue.h"
#include "Lib.h"
#include "PriorityQueue.h"

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

pthread_mutex_t bsns_queue_mutex;
pthread_cond_t bsns_queue_cond;
Queue bsns_c_queue;

pthread_mutex_t econ_queue_mutex;
pthread_cond_t econ_queue_cond;
Queue econ_c_queue;

/* Reading Input (Easy Money) */

Customer customerizeLine(char * input_line) {
	Customer customer;
	int type;
	sscanf(input_line, "%d:%d,%d,%d", &customer.uid,
								 &type,
								 &customer.arrival_time,
								 &customer.service_time);
	customer.type = (type == 1) ? 'B' : 'E';
	return customer;
}

#define error_tester(); fprintf(stderr, "Testing execution in %s in function %s at line %d\n", __FILE__, __func__, __LINE__);

unsigned int fget_customers(FILE * in, Customer ** customer_list) {
	char buffer[128];

	if(in == NULL) {
		error_handler(ERROR_fopen);
		exit(1);
	}

	// Get first line (number of customers)
	fgets(buffer, 128, in);
	int total_customers = 0;
	sscanf(buffer, "%d", &total_customers);

	if((*customer_list) == NULL) {
		error_tester();
		(*customer_list) = (Customer *) malloc(sizeof(Customer)*total_customers);
	} else {
		error_handler(ERROR_generic);
	}
	if((*customer_list) == NULL) {
		error_handler(ERROR_malloc);
	}

	// Get customers
	int i = 0;
	while(1) {
		char * test = fgets(buffer, 128, in);
		if(feof(in)) break;
		if(test == NULL || i >= total_customers) {
			error_handler(ERROR_fgets);
			exit(1);
		}
		(*customer_list)[i++] = customerizeLine(buffer);
	}
	return total_customers;
}

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
