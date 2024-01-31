// Sample solution for COMP1521 lab exercises
// count bits in a uint64_t

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// return how many 1 bits value contains
int q2(uint64_t value) {
    int count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}
