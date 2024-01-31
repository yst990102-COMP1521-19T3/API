// Print byte of a file in decimal,  hexadecimal and as ASCII if printable

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void process_file(char *pathname);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        process_file(argv[1]);
    }
    return 0;
}

void process_file(char *pathname) {
    FILE *stream = fopen(pathname, "r");
    if (stream == NULL) {
        perror(pathname);
        exit(1);
    }

    size_t n_bytes_read = 0;
    int byte;
    while ((byte = fgetc(stream)) != EOF) {
        printf("byte %4ld: %3d 0x%02x", n_bytes_read, byte, byte);
        if (isprint(byte)) {
            printf(" '%c'", byte);
        }
        printf("\n");
        n_bytes_read++;
    }

    fclose(stream);
}
