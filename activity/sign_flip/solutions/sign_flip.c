// Sample solution for COMP1521 lab exercises
//
// Extract the exponent of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "sign_flip.h"

#define SIGN_MASK (1u << 31)

// given the 32 bits of a float return the exponent
uint32_t sign_flip(uint32_t f) {
    return f ^= SIGN_MASK;
}
