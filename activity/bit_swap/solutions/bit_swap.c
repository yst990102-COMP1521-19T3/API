// COMP1521 19t3 ... test03_bit_swap: sample solution
// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    uint64_t new_value = 0;
    for (int i = 0; i < 64; i += 2) {
        uint64_t lower_bit = value & (((uint64_t)1) << i);
        uint64_t upper_bit = value & (((uint64_t)1) << (i + 1));
        new_value |= lower_bit << 1;
        new_value |= upper_bit >> 1;
    }
    return new_value;
}
