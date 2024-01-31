// Print position of first non-ASCII byte in file

#include <stdio.h>
#include <stdlib.h>

void process_file(char *pathname);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        process_file(argv[arg]);
    }
    return 0;
}

void process_file(char *pathname) {
    FILE *stream = fopen(pathname, "r");
    if (stream == NULL) {
        perror(pathname);
        exit(1);
    }

    ssize_t byte_position = 0;
    int byte;
    while ((byte = fgetc(stream)) != EOF) {
        if (byte > 127) {
            printf("%s: byte %zd is non-ASCII\n",  pathname, byte_position);
            return;
        }
        byte_position++;
    }

    fclose(stream);
    printf("%s is all ASCII\n", pathname);
}
