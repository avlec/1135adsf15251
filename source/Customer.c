#define _POSIX_C_SOURCE 199309L
#include "Customer.h"

#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Queue.h"
#include "Clerk.h"
#include "Lib.h"

extern unsigned int ms_time;

extern pthread_cond_t cond;
extern pthread_mutex_t mutex;

extern Clerk clerk[4];

extern SynchronousQueue buisness_queue;
extern SynchronousQueue economy_queue;

extern waiting_times times;

int check_clerks(int uid);

int check_clerks(int uid) {
	for(int i = 0; i < 4; ++i)
		if(clerk[i].cid == uid)
			return i;
	return -1;
}

void * customer_thread(void * param) {
	Customer * customer = (Customer *) param;
	
	SynchronousQueue * queue = NULL;
	if(customer->type == 'B')
		queue = &buisness_queue;
	else
		queue = &economy_queue;

	// As per assignment spec (line 68)
	printf("A customer arrives: customer ID %2d at %d.  \n", customer->uid, ms_time);
	
	// Add customer to proper queue.
	int length = sq_push(queue, *customer);
	// As per assignment spec (line 69)
	printf("A customer enters the queue: the queue 1, "
		   "and length of the queue %2d.  \n",
			length);

	int clerk = -1;
	
	if(pthread_mutex_lock(&mutex)) {
		error_handler(ERROR_pthread_mutex_lock);
		exit(1);
	}
	while( (clerk = check_clerks(customer->uid)) == -1 )
		if(pthread_cond_wait(&cond, &mutex)) {
			error_handler(ERROR_pthread_cond_wait);
			exit(1);
		}
	if(pthread_mutex_unlock(&mutex)) {
		error_handler(ERROR_pthread_mutex_unlock);
		exit(1);
	}
	
	add_waiting_time(&times, customer->arrival_time - ms_time, customer->type);

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

	free(customer);
	pthread_exit(0);
}


/*

	// Get lock on the mutex to check self (released by cond_wait, then acquired later)
	pq_lock(queue);
		
	// Continuously check the queue while the head of the queue isn't me
	while(sq_peek(queue).uid != customer->uid)
		pq_cond_wait(queue);
	
	// LOCK ACQUIRED (clerk and regular)
	pq_pop(queue); // remove me, i'm being served
	pq_clear_clerkid(queue);

	// Done with locks
	pq_unlock(queue);
	pq_clerk_unlock(queue);

*/

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
