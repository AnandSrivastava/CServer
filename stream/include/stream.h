/***********************************************************************************************************
* stream.h
*
* Stream interface to make it easier to do read/write through heterogeneous modules. By implementing stream
* methods one can provide an alternate source of data.
*
* Author - Anand Kumar 
************************************************************************************************************/

#ifndef __STREAM_H__
#define __STREAM_H__

#include "udef.h"

struct stream {
	//stream ptr to keep track of interface state/data
	stream_handle handle;
	int (*read)(stream_handle, char*, int);
	int (*write)(stream_handle, char*, int);
	void (*destroy)(struct stream*);
};

#endif
