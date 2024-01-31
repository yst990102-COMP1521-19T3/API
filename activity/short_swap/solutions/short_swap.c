// Sample solution for COMP1521 lab exercises
// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    uint16_t bottom_byte = value & 0xFF;
    uint16_t top_byte = value >> 8;
    return (bottom_byte << 8) | top_byte;
}
