/***********************************************************************************************************
* http_server.c
*
* CServer implementation.
*
* Author - Anand Kumar 
************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

#include "openssl/ssl.h"
#include "openssl/err.h"

#include "http_server.h"
#include "logger.h"
#include "socket_stream.h"
#include "socket_ssl_stream.h"
#include "request_router.h"
#include "request_parser.h"
#include "http_response.h"
#include "ssl_conn.h"

_router_ *router = NULL;
SSL_CTX *ctx = NULL;

//@see-def
void terminate(int sig) {
	//NEED TO ADD SAFE EXIT OF ROUTER
	close_router(router);
	router = NULL;
	if(ctx != NULL)
		SSL_CTX_free(ctx);
	LOG_DEBUG("...... SHUTTING DOWN");
	exit(0);
}

/*
* Reads and Http request and routes it to correct-handler through router handle
* @params st - stream to read/write through input stream
* @params router - router handle
* @return 0 if request is handled correctly.
*/
int handle_stream(struct stream *st, _router_ router) {
        struct http_request *r = parse_request(st);

#if DEBUG || LOG_ENABLED
        if(r != NULL) {
                LOG_DEBUG("CORRECTLY PARSED");
                LOG_DEBUG(r->endpoint);
                LOG_DEBUG(r->resource);
                LOG_DEBUG("METHOD AND ENDPOINT IDENTIFIED");

                struct http_header *header = r->header;
                while(header != NULL) {
                        header = header->next;
                }

                if(r->body_length > 0) {
                        LOG_DEBUG(r->body);
                }
        }
#endif

        LOG_DEBUG("ROUTING REQUEST");
        struct stream *r_stream = route_request(router, r->method, NULL, r->endpoint, r->resource, r->body, r->body_length);
        if(r_stream && r_stream->read) {
                send_200(st, r_stream);
                r_stream->destroy(r_stream);
        } else {
                send_404_method_not_found(st);
        }

	st->destroy(st);

        clear_request(r);

        return 0;
}

/*
* Reads and Http request and routes it to correct-handler through router handle
* @params client_socket - HTTP socket id at which client is connected.
* @params router - router handle
* @return 0 if request is handled correctly.
*/
int handle_request(int client_socket, _router_ router) {
	LOG_DEBUG("Processing request");
        struct stream *st = create_socket_stream(client_socket);
        
	return handle_stream(st, router);
}

/*
* Reads and Https request and routes it to correct-handler through router handle
* @params ctx - SSL context to be used to read through client_socket.
* @params client_socket - HTTP socket id at which client is connected.
* @params router - router handle
* @return 0 if request is handled correctly.
*/
int handle_ssl_request(SSL_CTX *ctx, int client_socket, _router_ router) {
	SSL *ssl = SSL_New_connect(ctx, client_socket);

	struct stream *st = create_ssl_socket_stream(ssl);
	return handle_stream(st, router);
}


//@see-def
int run(_router_ r) {
	if(r == NULL) {
		LOG_DEBUG("GIVEN APP IS NULL");
		return 1;
	}

	signal(SIGINT, terminate);

	if(router != NULL) {
		LOG_DEBUG("router is already setup.");
		return 1;
	}

	router = r;

	/* Initialize SSL library */
	ctx = Init_SSL();
	/****************************************************/

	//create socket
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//define address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(server_socket, 5);

	while(1) {
		int client_socket = accept(server_socket, NULL, NULL);
		LOG_DEBUG("CONNECTED TO CLIENT.......")
		handle_ssl_request(ctx, client_socket, router);

		LOG_DEBUG("REQUEST PROCESSED");
	}

	close_router(router);
	router = NULL;

	return 0;
}

