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

extern pthread_cond_t cond;
extern pthread_mutex_t mutex;

extern SynchronousQueue buisness_queue;
extern SynchronousQueue economy_queue;

extern int no_more_customers;

Customer check_queues();

Customer check_queues() {
	Customer customer = sq_pop(&buisness_queue);
	if(!check_customer(customer))
		return customer;
	return sq_pop(&economy_queue);
}

void * clerk_thread(void * param) {
	Clerk * self = (Clerk *)param;	

	while(1) {
		Customer customer = check_queues();
		
		if(check_customer(customer)) {
			if(no_more_customers)
				break;
			continue;	// While no customers are available, sleep
		}
		// Found customer
		
		// Set customer
		self->cid = customer.uid;

		// 		broadcast
		pthread_cond_broadcast(&cond);

		// As per assignment spec (line 70) 
		printf("A clerk starts serving a customer: "
			   "start time %.2f, the customer ID %2d, "
			   "the clerk ID %1d.  \n", (float)ms_time/10.0, customer.uid, self->uid);
		
		// join customer to me
		if(pthread_join(customer.thread, NULL)) {
			error_handler(ERROR_pthread_join);
			exit(1);
		}

		// As per assignment spec (line 71) 
		printf("A clerk finishes serving a customer: "
			   "end time %.2f, the customer ID %2d, "
			   "the clerk ID %1d.  \n", (float)ms_time/10.0, customer.uid, self->uid);
	}
	pthread_exit(0);
}

void clerk_init(Clerk * clerk, int uid) {
	clerk->uid = uid;
	clerk->cid = -1;
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
	Clerk * args = (Clerk *)  malloc(sizeof(Clerk));
	if(args == NULL) {
		error_handler(ERROR_malloc);
		exit(1);
	}
	if(pthread_create(&clerk->thread, &clerk->attr, clerk_thread, (void *) clerk)) {
		error_handler(ERROR_pthread_create);
		exit(1);
	}
}
