/***********************************************************************************************************
* request_router.h
*
* Request router which navigates incoming request to correct handler (controller). 
*
* Author - Anand Kumar 
************************************************************************************************************/

#ifndef __REQUEST_ROUTER_H__
#define __REQUEST_ROUTER_H__

#include "request.h"
#include "request_handler.h"

#include "stream.h"

#include "udef.h"

//Initializes router and @return router handle
_router_ init_router();

/*
* Registers an endpoint (string) and its handler.
* @params _router_ - a handle to router
* @params path - endpoint which uniquely identifies this handler
* @params handler - a rest request handler to serve incoming request on given endpoint
* @return 0 if registration successfull. 1 otherwise.
*/
int register_endpoint(_router_, char *path, struct request_handler *handler);

/*
* Routes a request to its truthful handler.
* @params _router_ - a handle to router
* @params HTTP_METHOD - Rest request method
* @params url_dict - additional request parameter.
* @params char
*/
struct stream* route_request(_router_, enum HTTP_METHOD, url_dict, char *e, char *r, char *b, size_t len);

/*
* Terminates current router
* @param _router_ - handle to router
*/
void close_router(_router_);

#endif
