#ifndef __{{name}}_ENDPOINT_H__
#define __{{name}}_ENDPOINT_H__

/***********************************************************************************************************
* {{name}}_endpoint.h
*
* All REST api (GET/POST/PUT/DELETE/PATCH) is to be handled here. 
* implementation is to be provided in {{name}}_endpoint.c .
* Author - <<auhthor_name>>
************************************************************************************************************/


#include "request_handler.h"

/*@return request_handler which contains the implementation of all REST endpoints.*/
struct request_handler* get_{{name}}_handler();

#endif
