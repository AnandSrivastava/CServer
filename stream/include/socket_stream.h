/***********************************************************************************************************
* socket_stream.h
*
* Socket stream which makes it easier to read/write through socket.
* Implementation : socket_stream.c
*
* Author - Anand Kumar
************************************************************************************************************/

#ifndef __SOCKET_STREAM_H__
#define __SOCKET_STREAM_H__

#include "stream.h"

struct stream *create_socket_stream(int socketid);

#endif
