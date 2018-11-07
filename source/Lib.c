#include <stdio.h>

#include "Lib.h"

/*		Helper Stuff 
 *	Will later turn this into a library.
 * */


void _error_handler(ErrorType et, const char * function, const char * file, int line) {
	switch(et) {
		case ERROR_fopen:
			fprintf(stderr,
				"Error opening file in function %s, in file %s, at line %d\n",
				function, file, line);
			break;
		case ERROR_malloc:
		case ERROR_calloc:
		case ERROR_realloc:
			fprintf(stderr,
				"Memory allocation error in function %s, in file %s, at line %d\n",
				function, file, line);
			break;
		case ERROR_pthread_join:
			fprintf(stderr,
				"Error joining threads in function %s, in file %s, at line %d\n",
				function, file, line);
			break;
		case ERROR_generic:
		default:
			fprintf(stderr,
				"Error in function %s, in file %s, at line %d\n",
				function, file, line);
	}
}

