/***********************************************************************************************************
* request_router.c
*
* Router implementation.
*
* Author - Anand Kumar 
************************************************************************************************************/

#include "request_router.h"
#include "url_encoded_dict.h"
#include "logger.h"
#include "utils.h"
#include "udef.h"

//@returns default handler of http-request. Adopts all orphan requests
extern struct request_handler* get_default_handler();

/*
* Router handle
* dict - stores mapping of endpoint to handler
* default_handler - default handler of all orphan request  
*/
struct inner_router {
	url_dict dict;
	struct request_handler *default_handler;
};

//@see-def
_router_ init_router() {
	struct inner_router *app = (struct inner_router*)malloc_safe(sizeof(struct inner_router));
	if(app != NULL) {
		LOG_DEBUG("created app");
		app->dict = create_dictionary();
		LOG_DEBUG("dictionary creates");
		app->default_handler = get_default_handler();
	}

	return app;
}

//@see-def
int register_endpoint(_router_ a, char *path, struct request_handler *handler) {
	struct inner_router *app = (struct inner_router*)a;
	return (app && (insert_into_dict(app->dict, path, handler) == 0)) ? 0 : 1;
}

//@see-def
struct stream* route_request(_router_ a, enum HTTP_METHOD method, url_dict params, char *endpoint, char *resource, char *body, size_t body_len) {
	struct stream* st = NULL;

	struct request_handler *handler = NULL;
	struct inner_router *rt = (struct inner_router*)a;
	if(rt != NULL) {
		LOG("app found");
		handler = get_from_dict(rt->dict, endpoint);
		if(handler == NULL) {
			LOG("handler is null");
			handler = rt->default_handler;
		}
	} else {
		LOG("invalid router");
	}

	if(handler) {
		LOG("Identifying callback");
		if(method == GET) {
			st = (handler->get) ? handler->get(resource, params) : NULL;
		} else if(method == POST) {
			st = (handler->post) ? handler->post(resource, params, body, body_len) : NULL;
		} else if(method == PUT) {
			st = (handler->put) ? handler->put(resource, params, body, body_len) : NULL;
		} else if(method == DELETE) {
			st = (handler->del) ? handler->del(resource, params, body, body_len) : NULL;
		} else if(method == PATCH) {
			st = (handler->patch) ? handler->patch(resource, params, body, body_len) : NULL;
		}
	} else {
		LOG("no handler found");
	}

	return st;
}

//@see-def
void close_router(_router_ a) {
	struct inner_router *app = (struct inner_router*)a;
	if(app != NULL) {
		clear_dictionary(app->dict);
		free_safe(app);
	}
}
