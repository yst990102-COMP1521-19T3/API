#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "float_exp.h"

#define EXPONENT_SHIFT 23
#define EXPONENT_MASK 0xFF

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f) {
    return (f >> EXPONENT_SHIFT) & EXPONENT_MASK;
}
