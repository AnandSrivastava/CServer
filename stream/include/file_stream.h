/***********************************************************************************************************
* file_stream.h
*
* File stream which makes it easier to read/write through a file. 
* Implementation : file_stream.c
*
* Author - Anand Kumar 
************************************************************************************************************/

#ifndef __FILE_STREAM_H__
#define __FILE_STREAM_H__
#include "stream.h"

struct stream *create_file_stream(char *filename);

#endif
