// Print position of first non-ASCII byte in file

#include <stdio.h>
#include <stdlib.h>

int compare_files(char *pathname1, char *pathname2);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    return compare_files(argv[1], argv[2]);
}

int compare_files(char *pathname1, char *pathname2) {
    FILE *stream1 = fopen(pathname1, "r");
    if (stream1 == NULL) {
        perror(pathname1);
        return 1;
    }

    FILE *stream2 = fopen(pathname2, "r");
    if (stream2 == NULL) {
        perror(pathname2);
        return 1;
    }

    ssize_t byte_position = 0;
    int byte1, byte2;
    while (1) {
        byte1 = fgetc(stream1);
        byte2 = fgetc(stream2);
        if (byte1 != byte2 || byte1 == EOF) {
            break;
        }
        byte_position++;
    }

    if (byte1 == byte2) {
        printf("Files are identical\n");
    } else if (byte1 == EOF) {
        printf("EOF on %s\n", pathname1);
    } else if (byte2 == EOF) {
        printf("EOF on %s\n", pathname2);
    } else {
        printf("Files differ at byte %zd\n", byte_position);
    }

    fclose(stream1);
    fclose(stream2);
    return 0;
}
