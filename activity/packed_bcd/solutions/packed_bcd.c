//
// Sample solution for COMP1521 lab exercises
//
// Convert a 8 digit Packed Binary Coded Decimal value to an integer

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer

uint32_t packed_bcd(uint32_t packed_bcd_value) {
    int result = 0;

    for (int i = N_BCD_DIGITS - 1; i >= 0; i--) {
        int decimal_digit = (packed_bcd_value >> (4 * i)) & 0xF;
        assert(decimal_digit < 10);
        result = result * 10 + decimal_digit;
    }

    return result;
}
