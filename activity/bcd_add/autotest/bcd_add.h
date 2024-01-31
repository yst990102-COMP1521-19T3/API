#ifndef BCD_ADD_H
#define BCD_ADD_H

typedef struct big_bcd {
	unsigned char *bcd;
	int n_bcd;
} big_bcd_t;

big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y);

void bcd_print(big_bcd_t *number);
void bcd_free(big_bcd_t *number);
#endif