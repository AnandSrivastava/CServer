/***********************************************************************************************************
* index.c
*
* This is default handler for any rest request to this cserver. When no endpoint is found response is being
* served from here. 
* Author - Anand Kumar 
************************************************************************************************************/
#include <string.h>

#include "request_handler.h"
#include "file_stream.h"
#include "logger.h"
#include "utils.h"

#define ROOT_FOLDER "www/"
#define INDEX_FILE "www/index.html"
#define NOT_FOUND_404 "www/method_not_implemented.html"

struct stream* default_get(char *resource, url_dict params) {
	char r_path[1024];

	memset(r_path, '\0', 1024*sizeof(char));
        if(resource != NULL) {
		LOG_DEBUG(resource);
                strcat_safe(r_path, 1024, ROOT_FOLDER, strlen(ROOT_FOLDER));
                strcat_safe(r_path, 1024, resource, strlen(resource));
        } else {
		LOG_DEBUG(INDEX_FILE);
                strcat_safe(r_path, 1024, INDEX_FILE, strlen(INDEX_FILE));
        }

        return create_file_stream(r_path);
}

struct stream* default_post(char *endpoint, url_dict params, char *content, size_t len) {
	return create_file_stream(NOT_FOUND_404);
}

struct stream* default_put(char *endpoint, url_dict params, char *content, size_t len) {
	return create_file_stream(NOT_FOUND_404);
}

struct stream* default_del(char *endpoint, url_dict params, char *content, size_t len) {
	return create_file_stream(NOT_FOUND_404);
}

struct stream* default_patch(char *endpoint, url_dict params, char *content, size_t len) {
	return create_file_stream(NOT_FOUND_404);
}

struct request_handler* get_default_handler() {
	struct request_handler *default_handler = (struct request_handler*)malloc_safe(sizeof(struct request_handler));
	LOG_DEBUG("creating default handler");
	if(default_handler != NULL) {
		default_handler->get = default_get;
		default_handler->post = default_post;
		default_handler->put = default_put;
		default_handler->del = default_del;
		default_handler->patch = default_patch;
	} else {
		LOG_ERROR("no default handler");
	}

	return default_handler;
}


