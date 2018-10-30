#ifndef DATATYPES_H
#define DATATYPES_H
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
	// TODO maybe some way to reference thread.
} Customer;

void print_customer(Customer customer);

#endif
