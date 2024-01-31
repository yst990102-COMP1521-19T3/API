// COMP1521 19T3 ... lab 1
// cat3: Copy input to output

#include <stdio.h>
#include <stdlib.h>

static void copy(FILE *, FILE *);

int main (void) {
    copy (stdin, stdout);
    return EXIT_SUCCESS;
}


// Copy contents of input to output, line-by-line
// Assumes both files open in appropriate mode
static void copy(FILE *input, FILE *output) {
    char buf[BUFSIZ] = {};
    while (fgets (buf, BUFSIZ, input) != NULL)
        fputs (buf, output);
}
