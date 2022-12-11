/***********************************************************************************************************
* http_response.h
*
* Common place to define general http response utility-method
*
* Author - Anand Kumar 
************************************************************************************************************/


#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include "stream.h"

/*
* sends a 404 response to out_stream
*/
int send_404_method_not_found(struct stream* out_stream);

/*
* Reads from in_stream and writes into out_stream (HTTP 200 response)
*/
int send_200(struct stream *out_stream, struct stream* in_stream);

#endif
