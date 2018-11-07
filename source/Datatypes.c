#include "Datatypes.h"

#include <stdio.h>
#include <stdlib.h>

#include "Lib.h"

void init_waiting_times(waiting_times * times, unsigned int size) {
	times->times = (waiting_time *) calloc(size, sizeof(waiting_time));
	if(times->times == NULL) {
		error_handler(ERROR_calloc);
		exit(EXIT_FAILURE);
	}
	times->count = 0;
	times->size = size;
	if(pthread_mutexattr_init(&times->mutexattr)) {
		error_handler(ERROR_pthread_mutexattr_init);
		exit(1);
	}
	if(pthread_mutex_init(&times->mutex, &times->mutexattr)) {
		error_handler(ERROR_pthread_mutex_init);
		exit(1);
	}
}

void add_waiting_time(waiting_times * times, unsigned int time, char cust_type) {
	if(pthread_mutex_lock(&times->mutex)) {
		error_handler(ERROR_pthread_mutex_lock);
		exit(EXIT_FAILURE);
	}
	times->times[times->count] = (waiting_time) { .time = time, .cust_type = cust_type };
	if(pthread_mutex_unlock(&times->mutex)) {
		error_handler(ERROR_pthread_mutex_unlock);
		exit(EXIT_FAILURE);
	}
}

float calc_avg_wait_all(waiting_times * times) {
	int count = times->size;
	int sum = 0;
	for(int i = 0; i < times->size; ++i)
		sum += times->times[i].time;
	return (float)sum/(float)count;

}
float calc_avg_wait_buisness(waiting_times * times) {
	int count = 0;
	int sum = 0;
	for(int i = 0; i < times->size; ++i) {
		if(times->times[i].cust_type == 'E')
			sum += times->times[i].time;
		++count;
	}
	return (float)sum/(float)count;
}

float calc_avg_wait_economy(waiting_times * times) {
	int count = 0;
	int sum = 0;
	for(int i = 0; i < times->size; ++i) {
		if(times->times[i].cust_type == 'E')
			sum += times->times[i].time;
		++count;
	}
	return (float)sum/(float)count;
}

void print_customer(Customer customer) {
	printf("Customer %d: %c, %d, %d\n",
			customer.uid,
			customer.type,
			customer.arrival_time,
			customer.service_time);
}

int check_customer(Customer customer) {
	if(customer.type == 'B' || customer.type == 'E') {
		return 0;
	}
	return 1;
}
