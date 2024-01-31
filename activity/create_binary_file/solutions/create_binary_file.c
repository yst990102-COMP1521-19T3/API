// Create a file containing the byte values specified on the command line

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s: <file> <byte0> <byte1> ...\n", argv[0]);
        exit(1);
    }

    FILE *stream = fopen(argv[1], "w");
    if (stream == NULL) {
        fprintf(stderr, "%s: ", argv[0]);
        perror(argv[1]);
        exit(1);
    }

    for (int arg = 2; arg < argc; arg++) {
        char *endptr;
        long l = strtol(argv[arg], &endptr, 0);

        if (argv[arg][0] == '\0' || *endptr != '\0' || l < 0 || l > 255) {
            fprintf(
                stderr, "%s: Invalid byte value '%s'\n", argv[0], argv[arg]
            );
            exit(1);
        }

        if (fputc((int)l, stream) == EOF) {
            fprintf(stderr, "%s: ", argv[0]);
            perror(argv[1]);
            exit(1);
        }
    }

    fclose(stream);
    return 0;
}
