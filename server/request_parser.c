/***********************************************************************************************************
* request-parser.c
*
* Basic HTTP-Request parser.
*
* Author - Anand Kumar 
************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "request_parser.h"
#include "logger.h"
#include "utils.h"

#define IS_CR_LF(buf, x,y) x < y && (*(buf+x) == '\r') && (x+1) < y && (*(buf+x+1) == '\n')
#define PARSER_BUFFER 1024
#define CONTENT_LENGTH "Content-Length"
#define CONTENT_HEADER_LEN 14
#define HTTP_VERBS_COUNT 5

/*
* Get the http method corresponding to a request string
* @params method - request string method
* @params len - method length
* @returns HTTP_METHOD (GET/POST/PUT/DELETE/PATCH/NONE)
*/
enum HTTP_METHOD get_method(const char *method,int len) {
	static char* verbs[] = { "GET", "POST", "PUT", "DELETE", "PATCH" };
	printf("checking method - {{%s}} len - %d\n",method, len);
	enum HTTP_METHOD ret = NONE;
	for(int i = 0;i<HTTP_VERBS_COUNT;i++) {
		if(strcmpi_safe(method, len, verbs[i], strlen(verbs[i])) == 0) {
			ret = (enum HTTP_METHOD)(i+1);
		}
	}

	return ret;
}

/*
* Creates a copy of given string. 
* @params s - input string 
* @param len - length to copy
* @returns a copy of given string upto given length
*/
char *create_string(const char *s, int len)
{
	char *dst = NULL;
	if(len > 0) {
		dst = (char*)malloc_safe(len+1);
		memcpy(dst, s, len);
	}

	return dst;
}

/*
* Extracts  methods and endpoint from request buffer.
* @params req - http_request to populate
* @params buf - request buffer
* @params buf_size - buffer size
* @returns 0
*/
int parse_method_and_endpoint(struct http_request *req, const char *buf, const int buf_size) {
	int i = 0;
	{
		while(i < buf_size && *(buf+i) == ' ') i++;

		int start = i, end = i;
		while(end < buf_size && *(buf+end) != ' ') end++;
		req->method = get_method(buf+start, end-start);
		i = end;
	}
	{
		while(i < buf_size && *(buf+i) == ' ') i++;
		if(i < buf_size && *(buf+i) == '/') i++;
		int start = i, end = i;
		while(end < buf_size && (*(buf+end) != ' ' && *(buf+end) != '/' && *(buf+end) != '?' && *(buf+end) != '#')) end++;
		req->endpoint = create_string(buf+start, end-start);
		i = end;
	}
	if(i < buf_size && *(buf+i) != ' ') {
		if(*(buf+i) == '/') i++;
		int start = i, end = i;
		while(end < buf_size && *(buf+end) != ' ') end++;
		req->resource = create_string(buf+start, end-start);
		LOG_DEBUG(req->resource);
	}

	return 0;
}

/*
* Extracts HTTP header name-value pair from given line. 
* @params buf - line buffer from http request
* @params buf_size - size of input buffer
* @returns http_header (name-value pair) from given line buffer
*/
struct http_header *parse_http_header(const char *buf, const int buf_size) {
	struct http_header *header = (struct http_header*)malloc_safe(sizeof(struct http_header));

	int i = 0;
	while(i < buf_size && *(buf+i) == ' ') i++;

	int name_start = i, name_end = i;
	while(name_end < buf_size && *(buf+name_end) != ':') name_end++;
	i = name_end+1;
	name_end--;
	while(name_end >= name_start && *(buf+name_end) == ' ') name_end--;
	header->name = create_string(buf+name_start, name_end-name_start+1);

	while(i < buf_size && *(buf+i) == ' ') i++;

	int value_start = i, value_end = buf_size;
	while(value_end >= value_start && *(buf+value_end) == ' ') value_end--;
	header->value = create_string(buf+value_start, value_end-value_start);

	LOG_DEBUG(header->name);
	LOG_DEBUG(header->value);

	return header;
}

//@see-def
struct http_request *parse_request(struct stream *fd) {
	int len = 0, cur_loc = 0, body_loc = 0, line_pos = 0;
	char buffer[PARSER_BUFFER], line[PARSER_BUFFER];
	memset(buffer, 0, PARSER_BUFFER*sizeof(char));

	struct http_request *req = (struct http_request*)malloc_safe(sizeof(struct http_request));
	do {
		if(cur_loc == len) {
			LOG_DEBUG("read next from stream.");
			len = fd->read(fd->handle, buffer, PARSER_BUFFER);
			if(len == 0) {
				LOG_DEBUG("reading done");
				break;
			}
		}
#if LOG_ENABLED
		printf("%c",buffer[cur_loc]);
#endif
		if(IS_CR_LF(buffer, cur_loc, len)) {
#if LOG_ENABLED
			printf("\n");
#endif
			LOG_DEBUG("FOUND CRLF");
			cur_loc += 2;
			if(req->method == NONE) {
				LOG_DEBUG("reading http line method and endpoint");
				parse_method_and_endpoint(req, line, line_pos);
			} else {
				LOG_DEBUG("Extracting Header");
				struct http_header *header = parse_http_header(line, line_pos);
				if(header != NULL) {
					if(strcmpi_safe(header->name, strlen(header->name), CONTENT_LENGTH, CONTENT_HEADER_LEN) == 0) {
						LOG_DEBUG("###copying content-length to http-request");
						LOG_DEBUG(header->value);
						req->body_length = atoi(header->value)+1;
						req->body = (char*) malloc_safe(req->body_length);
					}

					if(req->header == NULL) {
						req->header = header;
					}  else {
						struct http_header *temp = req->header;
						while(temp->next != NULL) {
							temp = temp->next;
						}
						temp->next = header;
					}
				}
			}

			if(IS_CR_LF(buffer, cur_loc, len)) {
                                LOG_DEBUG("reading http header");
                                cur_loc += 2;
				if(req->body_length > 0) {
					LOG_DEBUG("reading request body");
                	                memcpy_safe(req->body, req->body_length, buffer+cur_loc, len-cur_loc-1);
        	                        body_loc += len-cur_loc-1;
					while(len == PARSER_BUFFER) {
						len = fd->read(fd->handle, buffer, PARSER_BUFFER);
				                printf("HERE %d\n",len);
				                memcpy_safe(req->body+body_loc, req->body_length-body_loc, buffer, len);
				                body_loc += len;
					}
				}
                                break;
                        }

			line_pos = 0;
		}
		line[line_pos++] = buffer[cur_loc++];
	} while(1);

	return req;
}

