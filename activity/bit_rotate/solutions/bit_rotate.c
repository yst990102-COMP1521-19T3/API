#include "bit_rotate.h"

uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    uint32_t bits32 = bits;
    n_rotations = n_rotations % 16;
    if (n_rotations < 0) {
        n_rotations += 16;
    }
    bits32 <<= n_rotations;
    return (bits32 & 0xffff) | (bits32 >> 16);
}
