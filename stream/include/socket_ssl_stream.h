/***********************************************************************************************************
* socket_ssl_stream.h
*
* Socket stream which makes it easier to read/write through secure socket.
* Implementation : socket_ssl_stream.c
*
* Author - Anand Kumar
************************************************************************************************************/

#ifndef __SOCKET_SSL_STREAM_H__
#define __SOCKET_SSL_STREAM_H__

#include "openssl/ssl.h"
#include "stream.h"

struct stream *create_ssl_socket_stream(SSL *ssl);

#endif
