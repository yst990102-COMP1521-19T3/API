#include <stdio.h>
#include <string.h>

#include "serve_web_page.h"

// pathname is the pathname component of a URL
// if a corresponding file exists the client is sent
// a 200 header assuming file contains HTML
// followed by the file contents
// if a the file can't be opened
// a 404 header is sent with no body
void serve_web_page(char *pathname, FILE *client_stream) {

    // REPLACE WITH YOUR CODE
    fprintf(client_stream, HEADER_404);
    fprintf(client_stream, "You requested %s but function serve_web_page is unimplemented\n", pathname);

}
