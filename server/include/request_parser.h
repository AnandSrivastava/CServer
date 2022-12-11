/***********************************************************************************************************
* request_parser.h
*
* HTTP request parsing logic is to be implemented here. Generates HTTP Request/Header/Method and endpoint is 
* to be extracted through method here.
*
* Author - Anand Kumar 
************************************************************************************************************/

#ifndef __REQUEST_PARSER_H__
#define __REQUEST_PARSER_H__

#include "request.h"

/*
* parses http request content into http_request.
* @param fd - input stream to read http request content.
* @return http_request (request.h) C object from http request content.
*/
struct http_request *parse_request(struct stream* fd);

#endif
