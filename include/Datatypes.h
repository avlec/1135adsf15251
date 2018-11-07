#ifndef DATATYPES_H
#define DATATYPES_H

#include <pthread.h> 

typedef struct waiting_time {
	unsigned int time;
	char cust_type;
} waiting_time;

typedef struct waiting_times {
	struct waiting_time * times;
	int count;
	int size;
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutexattr;
} waiting_times;	

float calc_avg_wait_all(waiting_times * times);
float calc_avg_wait_buisness(waiting_times * times);
float calc_avg_wait_economy(waiting_times * times);

void init_waiting_times(waiting_times * times, unsigned int size);
void add_waiting_time(waiting_times * times, unsigned int time, char cust_type);

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
