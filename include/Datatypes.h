#ifndef DATATYPES_H
#define DATATYPES_H

#include <pthread.h> 

/*
 * uid 			: unique customer id
 * type 		: indicates buisness or economy, either 'B' or 'E'
 * arrival_time : time the customer is destined to arrive at the queue
 * service_time : time the customer needs to be helped by a clerk
 */
typedef struct Customer {
	unsigned int uid;
	char type;
	unsigned int arrival_time;
	unsigned int service_time;
	
	pthread_attr_t attr;
	pthread_t thread;
} Customer;

#define CUSTOMER_INITIALIZER { .uid = 0, .type = 'U', .arrival_time = 0, .service_time = 0 }

void print_customer(Customer customer);
int check_customer(Customer customer);

#endif
