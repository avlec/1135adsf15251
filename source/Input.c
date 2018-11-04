#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Input.h"
#include "Lib.h"

unsigned int read_input(Customer ** customer_list, char * filename) {
	FILE * inputfile = fopen(filename, "r");
	if(inputfile == NULL)
		error_handler(ERROR_fopen);
	unsigned int total_customers = fget_customers(inputfile, customer_list);
	fclose(inputfile);
	return total_customers;
}

Customer customerizeLine(char * input_line) {
	Customer customer;
	int type;
	sscanf(input_line, "%d:%d,%d,%d", &customer.uid,
								 &type,
								 &customer.arrival_time,
								 &customer.service_time);
	customer.type = (type == 1) ? 'B' : 'E';
	return customer;
}

#define error_tester(); fprintf(stderr, "Testing execution in %s in function %s at line %d\n", __FILE__, __func__, __LINE__);

unsigned int fget_customers(FILE * in, Customer ** customer_list) {
	char buffer[128];

	if(in == NULL) {
		error_handler(ERROR_fopen);
		exit(1);
	}

	// Get first line (number of customers)
	fgets(buffer, 128, in);
	int total_customers = 0;
	sscanf(buffer, "%d", &total_customers);

	if((*customer_list) == NULL) {
		error_tester();
		(*customer_list) = (Customer *) malloc(sizeof(Customer)*total_customers);
	} else {
		error_handler(ERROR_generic);
	}
	if((*customer_list) == NULL) {
		error_handler(ERROR_malloc);
	}

	// Get customers
	int i = 0;
	while(1) {
		char * test = fgets(buffer, 128, in);
		if(feof(in)) break;
		if(test == NULL || i >= total_customers) {
			error_handler(ERROR_fgets);
			exit(1);
		}
		(*customer_list)[i++] = customerizeLine(buffer);
	}
	return total_customers;
}
