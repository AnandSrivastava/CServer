/***********************************************************************************************************
* http_response.c
*
* HTTP response utility method
*
* Author - Anand Kumar 
************************************************************************************************************/

#include <stdio.h>
#include <string.h>

#include "http_response.h"
#include "logger.h"

#define MAX_SOCKET_WRITE_BUF_SIZE 1024
#define HTTP_OK "HTTP/1.1 200 OK\r\n\n\0"
#define NOT_FOUND_404 "www/method_not_implemented.html"
 
//@see-def
int send_404_method_not_found(struct stream* out_stream) {
        FILE *html_data;
        html_data = fopen(NOT_FOUND_404, "r");
        fseek(html_data, 0, SEEK_END);
        int fsize = ftell(html_data);
        fseek(html_data, 0, SEEK_SET);
        char response_data[1024];
        memset(response_data, 0, 1024*sizeof(char));

        fread(response_data, fsize, 1, html_data);

        char http_header[2048];
        memset(http_header, 0, 2048*sizeof(char));
        strcat(http_header, "HTTP/1.1 404 OK\r\n\n\0");
        strcat(http_header, response_data);
        LOG("RESPONDING TO CLIENT");
	int len = out_stream->write(out_stream->handle, http_header, fsize+20);
        fclose(html_data);

	return len;
}

//@see-def
int send_200(struct stream *out_stream, struct stream* in_stream) {
	int ret = 0;

	if(out_stream && in_stream) {
		char buf[MAX_SOCKET_WRITE_BUF_SIZE];
		int len = 0;
		ret = 19;
		out_stream->write(out_stream->handle, HTTP_OK, strlen(HTTP_OK));
		while((len = in_stream->read(in_stream->handle, buf, MAX_SOCKET_WRITE_BUF_SIZE)) > 0) {
			out_stream->write(out_stream->handle, buf, len);
			ret += len;
		}
	}

	return ret;
}
