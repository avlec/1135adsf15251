#ifndef CUSTOM_LIB_C
#define CUSTOM_LIB_C

typedef enum ErrorType {
	ERROR_generic,
	ERROR_fopen,
	ERROR_fgets,
	ERROR_malloc,
	ERROR_calloc,
	ERROR_realloc,

	ERROR_nanosleep,

	ERROR_pthread_mutexattr_init,
	ERROR_pthread_mutex_init,
	ERROR_pthread_mutex_lock,
	ERROR_pthread_mutex_unlock,
	ERROR_pthread_condattr_init,
	ERROR_pthread_cond_init,
	ERROR_pthread_cond_wait,
	ERROR_pthread_attr_init,
	ERROR_pthread_create,
	ERROR_pthread_join
} ErrorType;

#define error_handler(x) _error_handler(x, __func__, __FILE__, __LINE__)
void _error_handler(ErrorType et, const char * function, const char * file, int line); 

#endif
