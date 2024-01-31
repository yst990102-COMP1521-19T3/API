//
// Sample solution for COMP1521 lab exercises
//
// Convert a 2 digit Binary Code Decimal value to an integer

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a 2 digit BCD encoded value between 0 .. 9999
// return corresponding integer

int bcd(int bcd_value) {
    int bottom_digit = bcd_value & 0xF;
    assert(bottom_digit < 10);
    int top_digit = (bcd_value >> 8) & 0xF;
    assert(top_digit < 10);
    return top_digit * 10 + bottom_digit;
}
