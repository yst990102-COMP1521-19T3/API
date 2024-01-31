// Print on-ASCII bytes from file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_file(char *pathname);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        process_file(argv[arg]);
    }
    return 0;
}

void process_file(char *pathname) {
    FILE *in = fopen(pathname, "r");
    if (in == NULL) {
        perror(pathname);
        exit(1);
    }
    char *suffix = ".tmp.leave_only_ascii";
    char temporary_pathname[strlen(pathname) + strlen(suffix)  + 1];
    strcpy(temporary_pathname, pathname);
    strcat(temporary_pathname, suffix);

    FILE *out = fopen(temporary_pathname, "w");
    if (out == NULL) {
        perror(pathname);
        exit(1);
    }

    int byte;
    while ((byte = fgetc(in)) != EOF) {
        if (byte <= 127) {
            fputc(byte, out);
        }
    }
    fclose(in);
    fclose(out);

    // doesn't prevserve file permissions
    if (rename(temporary_pathname, pathname) != 0) {
        perror("rename");
        exit(1);
    }
}
