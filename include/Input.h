#ifndef INPUT_H
#define INPUT_H

#include "Datatypes.h"

unsigned int read_input(Customer ** customer_list, char * filename);
unsigned int fget_customers(FILE * in, Customer ** customer_list);
Customer customerizeLine(char * input_line);

#endif
