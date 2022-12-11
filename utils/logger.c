/***********************************************************************************************************
* logger.h
*
* Logger implementation
* TODO - Add redirection support in logger to store info anywhere.
*
* Author - Anand Kumar 
************************************************************************************************************/

#include <stdio.h>

#include "logger.h"

int log_error(const char *report, int line, const char *file, const char *func) {
#if LOG_ENABLED
	fprintf(stderr, "%s: %s : %s at %d\n",file, func, report, line);
#endif
	return 0;
}

int log_success(const char *report, int line, const char *file, const char *func) {
#if LOG_ENABLED
	fprintf(stdout, "%s: %s : %s at %d\n", file, func, report, line);
#endif
	return 0;
}

int log_debug(const char *report, int line, const char *file, const char *func) {
#if DEBUG
        fprintf(stdout, "%s: %s : %s at %d\n", file, func, report, line);
#endif
	return 0;
}

