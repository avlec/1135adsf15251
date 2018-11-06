#define _POSIX_C_SOURCE 199309L

#include "Clerk.h"

#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include "Queue.h"
#include "Lib.h"
#include "Datatypes.h"
	
struct timespec CLERK_SLEEP = {
#ifdef __DEBUG
	.tv_sec = 1,
	.tv_nsec = 0
#else
	.tv_sec = 0,
	.tv_nsec = 1000000
#endif
};

extern unsigned int ms_time;

extern SynchronousQueue buisness_queue;
extern SynchronousQueue economy_queue;

void clerk_init(Clerk * clerk, unsigned int clerk_id) {
	if(pthread_mutexattr_init(&clerk->mutex_attr)) {
		error_handler(ERROR_pthread_mutexattr_init);
		exit(1);
	}
	if(pthread_mutex_init(&clerk->mutex, &clerk->mutex_attr)) {
		error_handler(ERROR_pthread_mutex_init);
		exit(1);
	}
	if(pthread_condattr_init(&clerk->cond_attr)) {
		error_handler(ERROR_pthread_condattr_init);
		exit(1);
	}
	if(pthread_cond_init(&clerk->cond, &clerk->cond_attr)) {
		error_handler(ERROR_pthread_cond_init);
		exit(1);
	}
	if(pthread_attr_init(&clerk->attr)) {
		error_handler(ERROR_pthread_attr_init);
		exit(1);
	}
	void * args = malloc(sizeof(unsigned int));
	if(args == NULL) {
		error_handler(ERROR_malloc);
		exit(1);
	}
	memcpy(args, &clerk_id, sizeof(unsigned int));
	if(pthread_create(&clerk->thread, &clerk->attr, clerk_thread, args)) {
		error_handler(ERROR_pthread_create);
		exit(1);
	}
}

/*
 *
 *
 */
void * clerk_thread(void * param) {
	unsigned int clerk_id = *((unsigned int *)param);	

	while(1) {
		Customer customer;
		while(1) {
			// Check queues every 1ms
			if(nanosleep(&CLERK_SLEEP, NULL) < 0) {
				error_handler(ERROR_nanosleep);
				pthread_exit(NULL);
			}

			sq_lock(&buisness_queue);
			customer = sq_peek(&buisness_queue);	
			if(!check_customer(customer))	// buisness customer found
				break;
			sq_unlock(&buisness_queue);		// no buisness customer

			sq_lock(&economy_queue);
			customer = sq_peek(&economy_queue);
			if(!check_customer(customer))	// economy customer found
				break;
			sq_unlock(&economy_queue);		// no buisness customer
		}

		if(customer.type == 'B') {
			sq_wake(&buisness_queue);
		}
		if(customer.type == 'E') {
			sq_wake(&economy_queue);
		}

		// As per assignment spec (line 70) 
		printf("A clerk starts serving a customer: "
			   "start time %.2f, the customer ID %2d, "
			   "the clerk ID %1d  \n", (float)ms_time, customer.uid, clerk_id);
		/*	
		pthread_mutex_lock(&clerk[clerk_id].mutex);
		while(i_have_customer)
			pthread_cond_wait(&clerk[clerk_id].cond, &clerk[clerk_id].lock);
	*/

		// start customer thread
		// wait on my condition variable
		// wake up and reloop	
		
		// As per assignment spec (line 71) 
		printf("A clerk finishes serving a customer: "
			   "end time %.2f, the customer ID %2d, "
			   "the clerk ID %1d  \n", (float)ms_time, customer.uid, clerk_id);
	}
	pthread_exit(0);
}
