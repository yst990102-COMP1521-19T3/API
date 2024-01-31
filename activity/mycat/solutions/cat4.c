// COMP1521 19T3 ... lab 1
// cat4: Copy input to output

#include <stdio.h>
#include <stdlib.h>

static void copy(FILE *, FILE *);

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        copy (stdin, stdout);
    } else {
        for (int i = 1; i < argc; i++) {
            FILE *in;
            if ((in = fopen (argv[i], "r")) == NULL) {
                fprintf (stderr, "Can't read %s\n", argv[i]);
            } else {
                copy (in, stdout);
                fclose (in);
            }
        }
    }

    return EXIT_SUCCESS;
}


// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {
    int ch;
    while ((ch = getc (input)) != EOF) {
        putc(ch, output);
    }
}
