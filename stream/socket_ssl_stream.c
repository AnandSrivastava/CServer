/***********************************************************************************************************
* socket_ssl_stream.c
*
* Stream implementation to send/recv through ssl socket.
* TODO - extend other IO functionality 
*
* Author - Anand Kumar 
************************************************************************************************************/
#include <sys/socket.h>

#include "socket_ssl_stream.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "utils.h"

int ssl_socket_read(stream_handle handle, char *buffer, int len) {
	SSL *ssl = (SSL*)handle;
	return SSL_read(ssl, buffer, len);
}

int ssl_socket_write(stream_handle handle,  char *buf, int len) {
	SSL *ssl = (SSL*)handle;
	return SSL_write(ssl, buf, len);
}

void ssl_socket_destroy(struct stream *st) {
	if(st != NULL) {
		SSL *ssl = (SSL*)st->handle;
		int socket_id = SSL_get_fd(ssl);
		SSL_free(ssl);
		shutdown(socket_id, SHUT_WR);
		free_safe(st);
	}
}

////wraps the socket object within socket handler and creates a socket stream
////@return stream object pointer
struct stream *create_ssl_socket_stream(SSL *ssl) {
	struct stream *st = (struct stream*)malloc_safe(sizeof(struct stream));
	if(st != NULL) {
		st->handle = ssl;
		st->read = ssl_socket_read;
		st->write = ssl_socket_write;
		st->destroy = ssl_socket_destroy;
	}

	return st;
}
