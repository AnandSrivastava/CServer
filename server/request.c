/***********************************************************************************************************
* request.c
*
* http request object 
*
* Author - Anand Kumar 
************************************************************************************************************/

#include <stdio.h>

#include "request.h"
#include "logger.h"
#include "utils.h"

//@see-def
void clear_request(struct http_request *req) {
        if(req != NULL) {
		free_safe(req->endpoint);
		free_safe(req->resource);
                free_safe(req->body);

                struct http_header *header = req->header;
                while(header) {
                        struct http_header *next = header->next;
                        free_safe(header);
                        header = next;
                }

                free_safe(req);
        }
}

