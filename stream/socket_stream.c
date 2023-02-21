/***********************************************************************************************************
* socket_stream.c
*
* Stream implementation to send/recv through socket.
* TODO - extend other IO functionality 
*
* Author - Anand Kumar 
************************************************************************************************************/
#include <sys/socket.h>

#include "socket_stream.h"
#include "utils.h"

int socket_read(stream_handle handle, char *buffer, int len) {
	int socketid = *((int*)handle);
	return recv(socketid, buffer, len, 0);
}

int socket_write(stream_handle handle,  char *buf, int len) {
	int socketid = *((int*)handle);
	return send(socketid, buf, len, 0);
}

void socket_destroy(struct stream *st) {
	if(st != NULL) {
		int socket_id = *((int*)st->handle);
		shutdown(socket_id, SHUT_WR);

		free_safe(st->handle);
		free_safe(st);
	}
}

////wraps the socket object within socket handler and creates a socket stream
////@return stream object pointer
struct stream *create_socket_stream(int socketid) {
	struct stream *st = (struct stream*)malloc_safe(sizeof(struct stream));
	if(st != NULL) {
		int *socket_id = (int*)malloc_safe(sizeof(int));
		*socket_id = socketid;
		st->handle = socket_id;
		st->read = socket_read;
		st->write = socket_write;
		st->destroy = socket_destroy;
	}

	return st;
}
