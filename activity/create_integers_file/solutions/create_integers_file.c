// Create a file containomg integers one per line

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file> <start> <finish>\n", argv[0]);
        exit(1);
    }

    int start = atoi(argv[2]);
    int finish = atoi(argv[3]);

    FILE *stream = fopen(argv[1], "w");
    if (stream == NULL) {
        perror(argv[3]);
        exit(1);
    }

    int i = start;
    while (i <= finish) {
        fprintf(stream, "%d\n", i);
        i = i + 1;
    }

    fclose(stream);
    return 0;
}
