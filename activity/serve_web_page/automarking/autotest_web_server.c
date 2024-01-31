// A simple Web server

#include <stdio.h>
#include <assert.h>

#include "serve_web_page.h"

char *extract_pathname_http_request(char *http_request);
void handle_request(int client_fd);

#undef main

int main(int argc, char **argv) {
    FILE *dev_null = fopen("/dev/null", "w");
    assert(dev_null);
    FILE *client_stream = stdout;
    stdout = dev_null;
    for (int arg = 1; arg < argc; arg++) {
        serve_web_page(argv[arg], client_stream);
    }
    return 0;
}

