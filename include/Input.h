#ifndef INPUT_H
#define INPUT_H

#include "Datatypes.h"

Customer customerizeLine(char * input_line);
unsigned int fget_customers(FILE * in, Customer ** customer_list);

#endif
