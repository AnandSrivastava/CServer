/***********************************************************************************************************
* {{name}}_endpoint.c
*
* All requests to http://<<cserver_path>>:port/{{name}}/ is handled by this controller. 
*
* To handle rest method modify following methods
* GET - {{name}}_get
* POST - {{name}}_post
* PUT - {{name}}_put
* DELETE - {{name}}_del
* PATCH - {{name}}_patch
*
* Resource folder for this controller is www/{{name}}/
*
* Author - Anand Kumar 
************************************************************************************************************/

#include <string.h>

#include "request_handler.h"
#include "file_stream.h"
#include "logger.h"
#include "utils.h"
#include "{{name}}_endpoint.h"

#define ROOT_FOLDER "www/{{name}}/"
#define INDEX_FILE "www/{{name}}/index.html"
#define NOT_FOUND_404 "www/{{name}}/method_not_implemented.html"

struct stream* {{name}}_get(char *resource, url_dict params) {
	char r_path[1024];
	memset(r_path, '\0', 1024*sizeof(char));
	if(resource != NULL) {
		strcat_safe(r_path, 1024, ROOT_FOLDER, strlen(ROOT_FOLDER));
		strcat_safe(r_path, 1024, resource, strlen(resource));
	} else {
		strcat_safe(r_path, 1024, INDEX_FILE, strlen(INDEX_FILE));
	}

	return create_file_stream(r_path);
}

struct stream* {{name}}_post(char *endpoint, url_dict params, char *content, size_t len) {
	return create_file_stream(NOT_FOUND_404);
}

struct stream* {{name}}_put(char *endpoint, url_dict params, char *content, size_t len) {
	return create_file_stream(NOT_FOUND_404);
}

struct stream* {{name}}_del(char *endpoint, url_dict params, char *content, size_t len) {
	return create_file_stream(NOT_FOUND_404);
}

struct stream* {{name}}_patch(char *endpoint, url_dict params, char *content, size_t len) {
	return create_file_stream(NOT_FOUND_404);
}

struct request_handler* get_{{name}}_handler() {
	struct request_handler *{{name}}_handler = (struct request_handler*)malloc_safe(sizeof(struct request_handler));
	LOG_DEBUG("CREATING {{name}} HANDLER");
	if({{name}}_handler != NULL) {
		{{name}}_handler->get = {{name}}_get;
		{{name}}_handler->post = {{name}}_post;
		{{name}}_handler->put = {{name}}_put;
		{{name}}_handler->del = {{name}}_del;
		{{name}}_handler->patch = {{name}}_patch;
	} else {
		LOG_DEBUG("NO {{name}} HANDLE");
	}

	return {{name}}_handler;
}


