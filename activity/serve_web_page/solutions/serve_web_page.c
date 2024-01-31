#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "serve_web_page.h"

// pathname is the pathname component of a URL
// if a corresponding file exists the client is sent
// a 200 header which assumes file is HTML
// followed by the file contents
// if a the file can't be opened
// a 404 header is sent with no body
void serve_web_page(char *pathname, FILE *client_stream) {

    FILE *f = fopen(pathname, "r");

    if (f == NULL) {
        fputs(HEADER_404, client_stream);
        return;
    }

    fputs(HEADER_200, client_stream);

    // read file and set through socket to client
    int byte;
    while ((byte = fgetc(f)) != EOF) {
        fputc(byte, client_stream);
    }

}
