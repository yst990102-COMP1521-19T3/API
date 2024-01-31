#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mime_web_page.h"

#define HEADER_200_PRINTF "HTTP/1.1 200 OK\r\nContent-type: %s\r\n\r\n"


char *get_mime_type(char *pathname);

void mime_web_page(char *pathname, FILE *client_stream) {

    FILE *f = fopen(pathname, "r");

    if (f == NULL) {
        fputs(HEADER_404, client_stream);
        return;
    }

    char *mime_type = get_mime_type(pathname);
    if (mime_type == NULL) {
        fprintf(client_stream, HEADER_200_PRINTF, DEFAULT_MIME_TYPE);
    } else {
        fprintf(client_stream, HEADER_200_PRINTF, mime_type);
    }

    // read file and set through socket to client
    int byte;
    while ((byte = fgetc(f)) != EOF) {
        fputc(byte, client_stream);
    }

}

#define MIME_TYPES_MAX_LINE_LENGTH 8192

// returns a malloc'ed string containg appropriate mime-type for pathname
// by looking file suffix in /etc/mime-types
// return NULL if pathname does not contain '.' followed by 1+ characters
// return NULL if extension not found in /etc/mime-types

char *get_mime_type(char *pathname) {
    char *last_dot = strrchr(pathname, '.');

    if (last_dot == NULL) {
        return NULL;
    }
    char *extension = last_dot + 1;
    if (*extension == '\0') {
        return NULL;
    }

    // real /etc/mime.types searching for extension
    // reading this file for every request is inefficient
    // more effcient would be to read once and store in hash-table

    FILE *f = fopen("/etc/mime.types", "r");
    if (f == NULL) {
       return NULL;
    }

    char line[MIME_TYPES_MAX_LINE_LENGTH];
    while (fgets(line, sizeof line, f)) {

        // terminate line at comment character
        char *comment = strchr(line, '#');
        if (comment != NULL) {
            *comment = '\0';
        }

        char *saveptr;
        char *mime_type = strtok_r(line, " \t\r", &saveptr);
        if (mime_type == NULL) {
            continue;
        }

        // test if any extension listed for this mime-type
        // matches extension we have been given
        char *mime_type_extension;
        while ((mime_type_extension = strtok_r(NULL, " \t\r\n", &saveptr)) != NULL) {
            if (strcasecmp(mime_type_extension, extension) == 0) {
                fclose(f);
                return strdup(mime_type);
            }
        }
    }

    fclose(f);
    return NULL;
}
