// Read 10 numbers into an array
// then print the numbers which are
// larger than the last number read.

#include <stdio.h>

int main(void) {
    int i;
    int numbers[10] = { 0 };

    i = 0;
    while (i < 10) {
        scanf("%d", &numbers[i]);
        i++;
    }

    i = 0;
    while (i < 10) {
        if (numbers[i] > 0) {
            printf("%d\n", numbers[i]);
        }
        i++;
    }

    i = 0;
    while (i < 10) {
        if (numbers[i] < 0) {
            printf("%d\n", numbers[i]);
        }
        i++;
    }
}
