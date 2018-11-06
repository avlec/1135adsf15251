#ifndef CLERK_H
#define CLERK_H

#include <pthread.h>

typedef struct Clerk {
	pthread_t 		thread;
	pthread_attr_t 	attr;

	pthread_mutex_t mutex;
	pthread_mutexattr_t mutex_attr;

	pthread_cond_t 	cond;
	pthread_condattr_t cond_attr;
} Clerk;

void * clerk_thread(void * param);
void clerk_init(Clerk * clerk, unsigned int clerk_id);

#endif
