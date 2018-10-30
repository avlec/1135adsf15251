#ifndef CUSTOM_LIB_C
#define CUSTOM_LIB_C

typedef enum ErrorType {
	ERROR_generic,
	ERROR_fopen,
	ERROR_fgets,
	ERROR_malloc,
	ERROR_calloc,
	ERROR_realloc
} ErrorType;

#define error_handler(x) _error_handler(x, __func__, __FILE__, __LINE__)
void _error_handler(ErrorType et, const char * function, const char * file, int line); 

#endif
