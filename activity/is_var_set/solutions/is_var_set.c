// test the value of two environment are the same
// if so print 1, else print 0

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    assert(argc == 2);
    char *value = getenv(argv[1]);
    if (value != NULL && value[0] != '\0') {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}
