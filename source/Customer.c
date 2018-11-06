#define _POSIX_C_SOURCE 199309L
#include "Customer.h"

#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Queue.h"
#include "Lib.h"

extern unsigned int ms_time;

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
		int length = sq_push(&buisness_queue, *customer);
		// As per assignment spec (line 69)
		printf("A customer enters the queue: the queue 1, "
			   "and length of the queue %2d.  \n",
				length);
	}

	if(customer->type == 'E') {
		int length = sq_push(&economy_queue, *customer);
		// As per assignment spec (line 69)
		printf("A customer enters the queue: the queue 0, "
			   "and length of the queue %2d.  \n",
				length);
	}
	
	print_customer(*customer);
	printf("Waiting to be served!\n");
	
	// wait for turn
	// WILL HAVE A MUTEX LOCK WHEN WE GET HERE
	// check if it's me on the queue.

	for(;;);

	if(customer->type == 'B') {
		if(pthread_mutex_lock(&(buisness_queue.mutex))) {
			error_handler(ERROR_pthread_mutex_lock);
			exit(1);
		}
		while(sq_peek(&buisness_queue).uid != customer->uid)// while current top stack customer isn't me
			if(pthread_cond_wait(&(buisness_queue.cond), &(buisness_queue.mutex))) {
				error_handler(ERROR_pthread_cond_wait);
				exit(1);
			}
		if(pthread_mutex_unlock(&(buisness_queue.mutex))) {
			error_handler(ERROR_pthread_mutex_unlock);
			exit(1);
		}
	}
	if(customer->type == 'E') {
// Get lock on the mutex to check self
		if(pthread_mutex_lock(&(economy_queue.mutex))) {
			error_handler(ERROR_pthread_mutex_lock);
			exit(1);
		}
		while(0) // != customer.uid
			if(pthread_cond_wait(&(economy_queue.cond), &(economy_queue.mutex))) {
				error_handler(ERROR_pthread_cond_wait);
				exit(1);
			}
		if(pthread_mutex_unlock(&(economy_queue.mutex))) {
			error_handler(ERROR_pthread_mutex_unlock);
			exit(1);
		}
	}


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
