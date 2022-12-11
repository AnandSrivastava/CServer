/***********************************************************************************************************
* file_stream.c
*
* Stream implementation to IO through file.
* TODO - extend other IO functionality 
*
* Author - Anand Kumar 
************************************************************************************************************/

#include <stdio.h>

#include "file_stream.h"
#include "logger.h"
#include "utils.h"

int file_read(stream_handle handle, char* buffer, int len) {
	int total = -1;
	FILE *fp = (FILE*)handle;
	if(fp != NULL) {
		LOG_DEBUG("reading");
		total = fread(buffer, sizeof(char), len, fp);
	} else {
		LOG_ERROR("invalid file");
	}

	return total;
}

void file_destroy(struct stream *st) {
	if(st != NULL) {
		FILE* fp = (FILE*)(st->handle);
		fclose(fp);
		st->handle = NULL;
		free_safe(st);
	}
}

struct stream* create_file_stream(char *filename) {
	struct stream *st = NULL;

	FILE *fp = fopen(filename, "rb");
	LOG(filename);
	if(fp != NULL) {
		LOG_DEBUG("file opened successfully.");
		st = (struct stream*)malloc_safe(sizeof(struct stream));
		if(st != NULL) {
			st->handle = fp;
			st->read = file_read;
			st->destroy = file_destroy;
		}
	}

	return st;
}
