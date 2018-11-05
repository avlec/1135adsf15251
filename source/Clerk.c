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

	struct timespec CLERK_SLEEP;
#ifdef __DEBUG
	CLERK_SLEEP.tv_sec = 1;
	CLERK_SLEEP.tv_nsec = 0;//100000000L;
#else
	CLERK_SLEEP.tv_sec = 0;
	CLERK_SLEEP.tv_nsec = 1000000;
#endif

	while(1) {
		printf("Clerk %d ready, and waiting to serve a customer.\n", clerk_id);
		Customer customer;
		while(1) {
			// Check queues every 1ms
			
			if(nanosleep(&CLERK_SLEEP, NULL) < 0) {
				error_handler(ERROR_nanosleep);
				pthread_exit(NULL);
			}

			customer = sync_queue_pop(&buisness_queue);	
			if(!check_customer(customer)) // buisness class customer found
				break;
			
			customer = sync_queue_pop(&economy_queue);
			if(!check_customer(customer)) // economy class customer found
				break;
		}
		printf("Got customer");
	/*	
		pthread_mutex_lock(&clerk[clerk_id].mutex);
		while(i_have_customer)
			pthread_cond_wait(&clerk[clerk_id].cond, &clerk[clerk_id].lock);
	*/
		// start customer thread
		// wait on my condition variable
		// wake up and reloop	
	}
	pthread_exit(0);
}
