#include <stdio.h>
#include <stdint.h>
#include <assert.h>

int main(void) {
    uint32_t nuxi;

    scanf("%d", &nuxi);
    int index[256] = { 0 };

    for (int byte_position = 0; byte_position < 4; byte_position++) {
        uint8_t byte = (nuxi >> (8 * byte_position)) & 0xff;
        index[byte] = byte_position;
    }

    uint32_t number;
    scanf("%d", &number);

    uint32_t new_number = 0;

    for (int byte_position = 0; byte_position < 4; byte_position++) {
        uint32_t byte = (number >> (8 * byte_position)) & 0xff;
        int new_byte_position = index[(int)"UNIX"[byte_position]];
        // printf("byte[%d]=%x new_byte_position=%d\n", byte_position, byte, new_byte_position);
        assert(0 <= new_byte_position && new_byte_position < 4);
        new_number |= byte << (new_byte_position * 8);
    }

    printf("%d\n", new_number);
}
