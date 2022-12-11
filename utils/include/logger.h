/***********************************************************************************************************
* logger.h
*
* Centralized logger. 
* LOG_ENABLED - To enable all logging. 
* DEBUG - To enable Debug logging.
* Error is logged always.
*
* Author - Anand Kumar 
************************************************************************************************************/

#ifndef __LOGGER_H__
#define __LOGGER_H__

#define LOG_ERROR(report) log_error(report,  __LINE__, __FILE__, __func__);
#define LOG(report) log_success(report, __LINE__, __FILE__, __func__);
#define LOG_DEBUG(report) log_debug(report, __LINE__, __FILE__, __func__);

int log_debug(const char *report, int line, const char *file, const char *func);
int log_error(const char *report, int line, const char *file, const char *func);
int log_success(const char *report, int line, const char *file, const char *func);

#endif
