#define _POSIX_C_SOURCE 199309L
#include "Customer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "Lib.h"

extern SynchronousQueue buisness_queue;
extern SynchronousQueue economy_queue;

void customer_init(Customer customer) {
	Customer * args = malloc(sizeof(Customer));
	if(args == NULL) {
		error_handler(ERROR_malloc);
		exit(1);
	}
	
	memcpy(args, &customer, sizeof(Customer));
	
	if(pthread_attr_init(&args->attr)) {
		error_handler(ERROR_pthread_attr_init);
		exit(1);
	}
	if(pthread_create(&args->thread, &args->attr, customer_thread, (void *)args)) {
		error_handler(ERROR_pthread_create);
		exit(1);
	}
}

/*
 *
 *
 */
void * customer_thread(void * param) {
	Customer * customer = (Customer *) param;
	// As per assignment spec (line 68)
	printf("A customer arrives: customer ID %2d.  \n", customer->uid);
	
	// Add customer to proper queue.
	if(customer->type == 'B') {
		int length = sync_queue_push(&buisness_queue, *customer);
		// As per assignment spec (line 69)
		printf("A customer enters the queue: the queue 1, "
			   "and length of the queue %2d.  \n",
				length);
	}

	if(customer->type == 'E') {
		int length = sync_queue_push(&economy_queue, *customer);
		// As per assignment spec (line 69)
		printf("A customer enters the queue: the queue 0, "
			   "and length of the queue %2d.  \n",
				length);
	}
	
	print_customer(*customer);
	printf("Waiting to be served!\n");
	
	// wait for turn
	for(;;);

	// countdown service timer
	struct timespec CUST_SLEEP;
#ifdef __DEBUG
	CUST_SLEEP.tv_sec = 1*customer->service_time;
	CUST_SLEEP.tv_nsec = 0;//100000000L;
#else
	CUST_SLEEP.tv_sec = 0;
	CUST_SLEEP.tv_nsec = 1000000*customer->service_time; 
	// TODO math for this so it works
#endif
	if(nanosleep(&CUST_SLEEP, NULL) < 0) {
		error_handler(ERROR_nanosleep);
		pthread_exit(NULL);
	}
	
	// Wakeup clerk

	pthread_exit(0);
}
