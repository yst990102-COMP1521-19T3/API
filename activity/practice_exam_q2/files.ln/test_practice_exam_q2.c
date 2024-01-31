// count bits in a uint64_t

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int q2(uint64_t value);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        uint64_t s = strtoul(argv[arg], NULL, 0);

        printf("q2(0x%016lx) returned %d\n", s, q2(s));
    }

    return 0;
}
