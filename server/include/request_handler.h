/***********************************************************************************************************
* request_handler.h
*
* HTTP Request handler interface to be implemented by all controllers to provide full HTTP request support.
*
* Author - Anand Kumar 
************************************************************************************************************/

#ifndef __REQUEST_HANDLER_H__
#define __REQUEST_HANDLER_H__

#include <stddef.h>

#include "udef.h"

struct request_handler {
	struct stream* (*get)(char *endpoint, url_dict params);
	struct stream* (*post)(char *endpoint, url_dict params, char *content, size_t content_len);
	struct stream* (*put)(char *endpoint, url_dict params, char *content, size_t content_len);
	struct stream* (*del)(char *endpoint, url_dict params, char *content, size_t content_len);
	struct stream* (*patch)(char *endpoint, url_dict params, char *content, size_t content_len);
};

#endif
