/***********************************************************************************************************
* utils.c
*
* Safe version of C-library methods.
*
* Author - Anand Kumar 
************************************************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "utils.h"

//@see-def
void *malloc_safe(size_t size) {
	void *ptr = NULL;
	if(size > 0) {
		ptr = malloc(size);
		if(ptr == NULL) {
			fprintf(stderr, "Memory out of bound in %s at %ul for %ld", __FILE__, __LINE__, size);
			exit(EXIT_FAILURE);
		}
		memset(ptr, '\0', size);
	}

	return ptr;
}

//@see-def
void free_safe(void *ptr) {
	if(ptr != NULL)
		free(ptr);
}

//@see-def
int memcpy_safe(char *dst, size_t dst_len, char *src, size_t src_len) {
	if(dst_len > 0 && src_len > 0 && dst_len >= src_len) {
		memcpy(dst, src, src_len);
		return 0;
	}

	return 1;
}

//Checks if given character is alphanumeric
int isCharacter(char ch)
{
	return ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')); 
}

//@see-def
int strcmpi_safe(const char *str1, size_t s1_length, const char *str2, size_t s2_length) {
	while(s1_length > 0 && s2_length > 0) {
		if(!isCharacter(*str1) || tolower(*str1) == tolower(*str2)) {
			s1_length--; str1++;
			s2_length--; str2++;
		} else {
			return *str1-*str2;
		}
	}

	return 0;
}

//@see-def
char *strcat_safe(char *dst, size_t dst_len, char *src, size_t src_len) {
	int i = 0;
	while(*(dst+i) != '\0') i++;
	if(dst_len-i > src_len) {
		for(int j = 0;j<src_len;j++,i++) {
			*(dst+i) = *(src+j);
		}
		*(dst+i) = '\0';
	}

	return dst;
}
