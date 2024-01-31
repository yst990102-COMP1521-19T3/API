#ifndef WEB_PAGE_H
#define WEB_PAGE_H

#include <stdio.h>

#define HEADER_200 "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n"
#define HEADER_400 "HTTP/1.1 400 Bad request\r\n\r\n"
#define HEADER_404 "HTTP/1.1 404 Not Found\r\n\r\n"

#define DEFAULT_MIME_TYPE "application/octet-stream"

void mime_web_page(char *url, FILE *client_stream);
	
#endif