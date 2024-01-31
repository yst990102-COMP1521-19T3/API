// COMP1521 19t3 ... lab 3: bcd_add
// Add two arbitrary length Binary Coded Decimal Numbers
//
// 2019-10-06	Jashank Jeremy <jashank.jeremy@unsw.edu.au>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

//
// Store an arbitray length Binary Coded Decimal number.
// bcd points to an array of size n_bcd
// Each array element contains 1 decimal digit.
// Digits are stored in reverse order.
//
// For example if 42 is stored then
// n_bcd == 2
// bcd[0] == 0x02
// bcd[1] == 0x04
//

typedef struct big_bcd {
    unsigned char *bcd;
    int n_bcd;
} big_bcd_t;


big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y);
void bcd_print(big_bcd_t *number);
void bcd_free(big_bcd_t *number);
big_bcd_t *bcd_from_string(char *string);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <number>\n", argv[0]);
        exit(1);
    }

    big_bcd_t *left = bcd_from_string(argv[1]);
    big_bcd_t *right = bcd_from_string(argv[2]);

    big_bcd_t *result = bcd_add(left, right);

    bcd_print(result);
    printf("\n");

    bcd_free(left);
    bcd_free(right);
    bcd_free(result);

    return 0;
}


// DO NOT CHANGE THE CODE ABOVE HERE

typedef unsigned char bcd;

big_bcd_t *bcd_add (big_bcd_t *x, big_bcd_t *y)
{
	assert (x != NULL);
	assert (y != NULL);

	struct big_bcd *new = calloc (1, sizeof *new);
	assert (new != NULL);
	*new = (struct big_bcd) { .bcd = NULL, .n_bcd = 0 };

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#define bcd_push(obj,i,n) \
	({ \
		(obj)->bcd = realloc ((obj)->bcd, (size_t) ++((obj)->n_bcd)); \
		(obj)->bcd[(i)] = (n); \
	})

	bcd carry = 0;
	int i = 0;
	while (i < max (x->n_bcd, y->n_bcd)) {
		bcd xa = i < x->n_bcd ? x->bcd[i] : 0;
		bcd yb = i < y->n_bcd ? y->bcd[i] : 0;
		assert (
			0 <= xa && xa <= 9 &&
			0 <= yb && yb <= 9
		);

		bcd result = xa + yb + carry;
		assert (0 <= result);

		carry  = result / 10;
		result = result % 10;
		assert (0 <= carry);
		assert (0 <= result && result <= 9);

		bcd_push (new, i, result);
		i++;
	}

	assert (i == max (x->n_bcd, y->n_bcd));

	assert (i == new->n_bcd);
	assert (new->n_bcd == 0 || new->bcd != NULL);

	if (carry)
		bcd_push (new, i, carry);

	assert (i == new->n_bcd || i + 1 == new->n_bcd);

#undef bcd_push

	return new;
}


// DO NOT CHANGE THE CODE BELOW HERE


// print a big_bcd_t number
void bcd_print(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    assert(number->n_bcd > 0);
    for (int i = number->n_bcd - 1; i >= 0; i--) {
        putchar(number->bcd[i] + '0');
    }
}

// free storage for big_bcd_t number
void bcd_free(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    // or it is calling free for the numbers it is given
    free(number->bcd);
    free(number);
}

// convert a string to a big_bcd_t number
big_bcd_t *bcd_from_string(char *string) {
    big_bcd_t *number = malloc(sizeof *number);
    assert(number);

    int n_digits = strlen(string);
    assert(n_digits);
    number->n_bcd = n_digits;

    number->bcd = malloc(n_digits * sizeof number->bcd[0]);
    assert(number->bcd);

    for (int i = 0; i < n_digits; i++) {
        int digit = string[n_digits - i - 1];
        assert(isdigit(digit));
        number->bcd[i] = digit - '0';
    }

    return number;
}
