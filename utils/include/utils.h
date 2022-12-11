/***********************************************************************************************************
* utils.h
*
* Safe version of utility method to C-library method. 
*
* Author - Anand Kumar 
************************************************************************************************************/

#ifndef __UTILS_H__
#define __UTILS_H__

#include <string.h>

//Allocates memory if enough space is there. For invalid size return NULL
void* malloc_safe(size_t size);

//Checks for valid ptr before freeing up space.
void free_safe(void* ptr);

/*
* Copies content from src into dst. 
* @param dst - destination store
* @param dst_len - total length of destination store
* @param src - source store
* @param src_len - total length of data to be copied from source store.
* @return 0 if copy is successful 1 otherwise
*/
int memcpy_safe(char *dst, size_t dst_len, char *src, size_t src_len);

/*
* Case in-sensitive comparision of two string. 
* @param str1 - string one
* @param s1_length - string one length
* @param str2 - string two
* @param s2_length - string two length
* @return 0 if both are same otherwise it returns the diff on last mismatch
*/
int strcmpi_safe(const char *str1, size_t s1_length, const char *str2, size_t s2_length);

/*
* Appends source string into destination string. 
* @param dst - destination store
* @param dst_len - total length of destination store
* @param src - source store
* @param src_len - total length of data to be copied from source store.
* @return destination string pointer
*/
char *strcat_safe(char *dst, size_t dst_len, char *src, size_t src_len);

#endif
