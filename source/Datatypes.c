#include <stdio.h>

#include "Datatypes.h"

void print_customer(Customer customer) {
	printf("Customer %d: %c, %d, %d\n",
			customer.uid,
			customer.type,
			customer.arrival_time,
			customer.service_time);
}

int check_customer(Customer customer) {
	if(customer.type != 'B' || customer.type != 'E')
		return -1;
	return 0;
}
