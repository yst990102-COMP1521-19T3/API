#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

/*
Compiles to one instruction

popcnt  rax, rdi
ret
*/
int bit_count(uint64_t value) {
    int count = 0;
    while (value) {
        count++;
        value &= (value - 1); // fun bit twiddling
    }
    return count;
}
