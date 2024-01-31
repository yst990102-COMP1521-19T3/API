// float_bits.c
// Sample solution for COMP1521 lab exercises
// Dylan Brotherston
//
// The following code changes main()
// in order to implement full error checking on the input
// when converting to a float
//
// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// Required for float conversion error checking
#include <errno.h> // errno
#include <math.h>  // HUGE_VALF

//
// We use this union to obtain the raw bits of a float
// by storing the float in the f field
// and then using the u field to obtain the bits
//
union overlay {
    float f;
    uint32_t u;
};

//
// A struct suitable for storing the 3 components of a float
//

typedef struct float_components {
    uint32_t sign;
    uint32_t exponent;
    uint32_t fraction;
} float_components_t;

float_components_t float_bits(uint32_t bits);
int is_nan(float_components_t f);
int is_positive_infinity(float_components_t f);
int is_negative_infinity(float_components_t f);
int is_zero(float_components_t f);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        union overlay input;

        errno = 0; // error number: set to 0 to clear previous errors
        char *endptr =
            NULL; // create a pointer to pass to strtof for error checking
        input.f = strtof(argv[arg], &endptr); // strtof - string to float
        if (endptr == argv[arg]) {
            // If endptr is set to the start of the string
            // then no conversion occured, eg. invalid syntax
            fprintf(stderr, "%s: Could not convert \"%s\" to float\n", argv[0],
                    endptr);
            return 1;
        }
        if (*endptr != '\0') {
            // If endptr is not the start of the string AND not the end of the string
            // then a conversion occured but extra characters were appended
            fprintf(stderr,
                    "%s: Non digit characters after float value: \"%s\"\n",
                    argv[0], endptr);
            return 1;
        }
        if (errno) {
            // If errno is set the an error occored
            // only possible error is ERANGE - value out of range
            if (input.f == HUGE_VALF || input.f == -HUGE_VALF) {
                // input value was to large for a float
                // |value| > ~10^38
                fprintf(stderr,
                        "%s: Value to big, float will overflow: \"%s\"\n",
                        argv[0], argv[arg]);
            }
            if (input.f == 0.0f) {
                // input value was to small for a float
                // |value| < ~10^-44
                fprintf(stderr,
                        "%s: Value to small, float will underflow: \"%s\"\n",
                        argv[0], argv[arg]);
            }
            return 1;
        }

        float_components_t c = float_bits(input.u);

        printf("float_bits(%.9g) returned\n", input.f);
        printf("sign = 0x%x\n", c.sign);
        printf("exponent = 0x%02x\n", c.exponent);
        printf("fraction = 0x%06x\n", c.fraction);

        printf("is_nan returned: %d\n", is_nan(c));
        printf("is_positive_infinity returned: %d\n", is_positive_infinity(c));
        printf("is_negative_infinity returned: %d\n", is_negative_infinity(c));
        printf("is_zero returned: %d\n", is_zero(c));
    }

    return 0;
}

// DO NOT CHANGE THE CODE ABOVE HERE

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    return (float_components_t){ (f >> 31) & 0x1, (f >> 23) & 0xFF,
                                 (f >> 0) & 0x7FFFFF };
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    return f.exponent == 0xFF && f.fraction > 0x0;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    return f.sign == 0x0 && f.exponent == 0xFF && f.fraction == 0x0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    return f.sign == 0x1 && f.exponent == 0xFF && f.fraction == 0x0;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    return f.exponent == 0x0 && f.fraction == 0x0;
}
