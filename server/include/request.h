/***********************************************************************************************************
* request.h
*
* HTTP Request and Header structures. All object corresponding to HTTP request should be declared here.
*
* Author - Anand Kumar 
************************************************************************************************************/

#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <stddef.h>

#include "stream.h"

//Enumeration for top HTTP methods
enum HTTP_METHOD {
	NONE,
	GET,
	POST,
	PUT,
	DELETE,
	PATCH
};

/*
* HTTP header list (All headers are stored as a link-list)
* name - HTTP header name
* value - HTTP header value (corresponding to given name)
* next - Next HTTP Header
*/
struct http_header {
	char *name;
	char *value;
	struct http_header *next;
};

/*
* HTTP request structure
* method - HTTP method (GET/PUT/POST/PUT/DELETE/PATCH)
* endpoint - endpoint at which request is targetted (controller)
* resource - resource which is being accessed here.
* header - HTTP header linked-list
* body - HTTP request body
* body_length - HTTP request body-length
*/ 
struct http_request {
	enum HTTP_METHOD method;
	char *endpoint;
	char *resource;
	struct http_header *header;

	char *body;
	size_t body_length;
};

// Frees-up space taken up by http request
void clear_request(struct http_request *req);

#endif
