#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "implementations.h"
#include "instructions.h"
#include "ram.h"
#include "registers.h"
#include "syscalls.h"

static uint32_t get_key(char ident, uint32_t op, instruction_info i) {
    uint32_t mask = ~((~0u) >> 1), key = 0;
    char *mask_start = strchr(i.encoding, ident);
    char *mask_end = strrchr(i.encoding, ident);
    char *encoding_end = strchr(i.encoding, '\0');
    for (char *_ = i.encoding; _ != mask_start; mask >>= 1, _++) {
    }
    for (char *_ = mask_start; _ <= mask_end; mask >>= 1, _++) {
        key |= op & mask;
    }
    key >>= (encoding_end - mask_end) - 1;

    return key;
}

static uint32_t N_bit_2_comp(char ident, uint32_t key, instruction_info i) {
    char *mask_start = strchr(i.encoding, ident);
    char *mask_end = strrchr(i.encoding, ident);
    uint32_t key_bits = (uint32_t)(mask_end - mask_start) + 1;
    if (key & 1ul << (key_bits - 1)) {
        uint32_t mask = ~((~0u) >> 1);
        while (!(key & mask)) {
            key |= mask;
            mask >>= 1;
        }
    }
    return key;
}

int implementation_ADD(uint32_t op, instruction_info i, uint32_t *pc) {
    int64_t x = get_register(get_key('S', op, i));
    int64_t y = get_register(get_key('T', op, i));

    int64_t z = x + y;

    if (z > INT64_MAX || z < INT64_MIN) {
        fprintf(stderr, "IntegerOverflow\n");
        exit(2);
    }

    set_register(get_key('D', op, i), (uint32_t)z);

    *pc += 4;
    return -1;
}

int implementation_ADDU(uint32_t op, instruction_info i, uint32_t *pc) {
    int64_t x = get_register(get_key('S', op, i));
    int64_t y = get_register(get_key('T', op, i));

    int64_t z = x + y;

    set_register(get_key('D', op, i), (uint32_t)z);

    *pc += 4;
    return -1;
}

int implementation_ADDI(uint32_t op, instruction_info i, uint32_t *pc) {
    int64_t x = get_register(get_key('S', op, i));
    int64_t y = get_key('I', op, i);
    y = N_bit_2_comp('I', (uint32_t)y, i);

    int64_t z = x + y;

    if (z > INT64_MAX || z < INT64_MIN) {
        fprintf(stderr, "IntegerOverflow\n");
        exit(2);
    }

    set_register(get_key('T', op, i), (uint32_t)z);

    *pc += 4;
    return -1;
}

int implementation_ADDIU(uint32_t op, instruction_info i, uint32_t *pc) {
    int64_t x = get_register(get_key('S', op, i));
    int64_t y = get_key('I', op, i);
    y = N_bit_2_comp('I', (uint32_t)y, i);

    int64_t z = x + y;

    set_register(get_key('T', op, i), (uint32_t)z);

    *pc += 4;
    return -1;
}

int implementation_SUB(uint32_t op, instruction_info i, uint32_t *pc) {
    int64_t x = get_register(get_key('S', op, i));
    int64_t y = get_register(get_key('T', op, i));

    int64_t z = x - y;

    if (z > INT64_MAX || z < INT64_MIN) {
        fprintf(stderr, "IntegerOverflow\n");
        exit(2);
    }

    set_register(get_key('D', op, i), (uint32_t)z);

    *pc += 4;
    return -1;
}

int implementation_SUBU(uint32_t op, instruction_info i, uint32_t *pc) {
    int64_t x = get_register(get_key('S', op, i));
    int64_t y = get_register(get_key('T', op, i));

    int64_t z = x - y;

    set_register(get_key('D', op, i), (uint32_t)z);

    *pc += 4;
    return -1;
}

int implementation_MUL(uint32_t op, instruction_info i, uint32_t *pc) {
    int64_t x = get_register(get_key('S', op, i));
    int64_t y = get_register(get_key('T', op, i));

    int64_t z = x * y;

    set_register(get_key('D', op, i), (uint32_t)z);

    *pc += 4;
    return -1;
}

/*
int implementation_MULT(uint32_t op, instruction_info i, uint32_t *pc) {
    int64_t x = get_register(get_key('S', op, i));
    int64_t y = get_register(get_key('T', op, i));

    // overflow should cause capping at INT64_MAX or INT64_MIN
    int64_t z = x * y;

    set_hi((uint32_t)(((uint64_t)z & 0xFFFFFFFF00000000) >> 32));
    set_lo((uint32_t)((uint64_t)z & 0x00000000FFFFFFFF));

    *pc += 4;
    return -1;
}

int implementation_MULTU(uint32_t op, instruction_info i, uint32_t *pc) {
    uint64_t x = get_register(get_key('S', op, i));
    uint64_t y = get_register(get_key('T', op, i));

    uint64_t z = x * y;

    set_hi((uint32_t)((z & 0xFFFFFFFF00000000) >> 32));
    set_lo((uint32_t)(z & 0x00000000FFFFFFFF));

    *pc += 4;
    return -1;
}

int implementation_DIV(uint32_t op, instruction_info i, uint32_t *pc) {
    int64_t x = get_register(get_key('S', op, i));
    int64_t y = get_register(get_key('T', op, i));

    {
        int64_t z = x / y;
        set_lo((uint32_t)z);
    }

    {
        int64_t z = x % y;
        set_hi((uint32_t)z);
    }

    *pc += 4;
    return -1;
}

int implementation_DIVU(uint32_t op, instruction_info i, uint32_t *pc) {
    uint64_t x = get_register(get_key('S', op, i));
    uint64_t y = get_register(get_key('T', op, i));

    {
        uint64_t z = x / y;
        set_lo((uint32_t)z);
    }

    {
        uint64_t z = x % y;
        set_hi((uint32_t)z);
    }

    *pc += 4;
    return -1;
}

int implementation_MTHI(uint32_t op, instruction_info i, uint32_t *pc) {
    set_hi(get_register(get_key('S', op, i)));

    *pc += 4;
    return -1;
}

int implementation_MFHI(uint32_t op, instruction_info i, uint32_t *pc) {
    set_register(get_key('D', op, i), get_hi());

    *pc += 4;
    return -1;
}

int implementation_MTLO(uint32_t op, instruction_info i, uint32_t *pc) {
    set_lo(get_register(get_key('S', op, i)));

    *pc += 4;
    return -1;
}

int implementation_MFLO(uint32_t op, instruction_info i, uint32_t *pc) {
    set_register(get_key('D', op, i), get_lo());

    *pc += 4;
    return -1;
}
*/

int implementation_AND(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('S', op, i));
    uint32_t y = get_register(get_key('T', op, i));

    uint32_t z = x & y;

    set_register(get_key('D', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_ANDI(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('S', op, i));
    uint32_t y = get_key('U', op, i);

    uint32_t z = x & y;

    set_register(get_key('T', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_OR(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('S', op, i));
    uint32_t y = get_register(get_key('T', op, i));

    uint32_t z = x | y;

    set_register(get_key('D', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_ORI(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('S', op, i));
    uint32_t y = get_key('U', op, i);

    uint32_t z = x | y;

    set_register(get_key('T', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_XOR(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('S', op, i));
    uint32_t y = get_register(get_key('T', op, i));

    uint32_t z = x ^ y;

    set_register(get_key('D', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_XORI(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('S', op, i));
    uint32_t y = get_key('U', op, i);

    uint32_t z = x ^ y;

    set_register(get_key('T', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_SLLV(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('T', op, i));
    uint32_t y = get_register(get_key('S', op, i));

    uint32_t z = x << (y & 0x1F);

    set_register(get_key('D', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_SLL(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('T', op, i));
    uint32_t y = get_key('U', op, i);

    uint32_t z = x << y;

    set_register(get_key('D', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_SRLV(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('T', op, i));
    uint32_t y = get_register(get_key('S', op, i));

    uint32_t z = x >> (y & 0x1F);

    set_register(get_key('D', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_SRL(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('T', op, i));
    uint32_t y = get_key('U', op, i);

    uint32_t z = x >> y;

    set_register(get_key('D', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_SLT(uint32_t op, instruction_info i, uint32_t *pc) {
    int32_t x = get_register(get_key('S', op, i));
    int32_t y = get_register(get_key('T', op, i));

    bool z = x < y;

    set_register(get_key('D', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_SLTU(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('S', op, i));
    uint32_t y = get_register(get_key('T', op, i));

    bool z = x < y;

    set_register(get_key('D', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_SLTI(uint32_t op, instruction_info i, uint32_t *pc) {
    int32_t x = (int32_t)get_register(get_key('S', op, i));
    int32_t y = (int32_t)get_key('I', op, i);
    y = (int32_t)N_bit_2_comp('I', (uint32_t)y, i);

    bool z = x < y;

    set_register(get_key('T', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_SLTIU(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = (int32_t)get_register(get_key('S', op, i));
    uint32_t y = (int32_t)get_key('I', op, i);
    y = (uint32_t)N_bit_2_comp('I', (uint32_t)y, i);

    bool z = x < y;

    set_register(get_key('T', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_LUI(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_key('U', op, i);

    uint32_t z = x << 16;

    set_register(get_key('T', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_LB(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('B', op, i));
    uint32_t y = get_key('O', op, i);
    y = N_bit_2_comp('O', y, i);

    uint32_t z = 0;
    for (unsigned int b = 0; b < 1; b++) {
        z <<= 8;
        z |= get_byte(x + y + (1 - b - 1));
    }

    if (z & 0x80)
        z |= 0xFFFFFF00;

    set_register(get_key('T', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_LH(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('B', op, i));
    uint32_t y = get_key('O', op, i);
    y = N_bit_2_comp('O', y, i);

    uint32_t z = 0;
    for (unsigned int b = 0; b < 2; b++) {
        z <<= 8;
        z |= get_byte(x + y + (2 - b - 1));
    }

    if (z & 0x8000)
        z |= 0xFFFF0000;

    set_register(get_key('T', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_LW(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_register(get_key('B', op, i));
    uint32_t y = get_key('O', op, i);
    y = N_bit_2_comp('O', y, i);

    uint32_t z = 0;
    for (unsigned int b = 0; b < 4; b++) {
        z <<= 8;
        z |= get_byte(x + y + (4 - b - 1));
    }

    set_register(get_key('T', op, i), z);

    *pc += 4;
    return -1;
}

int implementation_SB(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t z = get_register(get_key('T', op, i));
    uint32_t x = get_register(get_key('B', op, i));
    uint32_t y = get_key('O', op, i);
    y = N_bit_2_comp('O', y, i);

    for (unsigned int b = 0; b < 1; b++) {
        set_byte(x + y + b, z & 0xFF);
        z >>= 8;
    }

    *pc += 4;
    return -1;
}

int implementation_SH(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t z = get_register(get_key('T', op, i));
    uint32_t x = get_register(get_key('B', op, i));
    uint32_t y = get_key('O', op, i);
    y = N_bit_2_comp('O', y, i);

    for (unsigned int b = 0; b < 2; b++) {
        set_byte(x + y + b, z & 0xFF);
        z >>= 8;
    }

    *pc += 4;
    return -1;
}

int implementation_SW(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t z = get_register(get_key('T', op, i));
    uint32_t x = get_register(get_key('B', op, i));
    uint32_t y = get_key('O', op, i);
    y = N_bit_2_comp('O', y, i);

    for (unsigned int b = 0; b < 4; b++) {
        set_byte(x + y + b, z & 0xFF);
        z >>= 8;
    }

    *pc += 4;
    return -1;
}

int implementation_BEQ(uint32_t op, instruction_info i, uint32_t *pc) {
    int32_t x = (int32_t)get_register(get_key('S', op, i));
    int32_t y = (int32_t)get_register(get_key('T', op, i));
    int32_t z = (int32_t)get_key('I', op, i);
    z = (int32_t)N_bit_2_comp('I', (uint32_t)z, i);

    if (x == y) {
        *pc = (uint32_t)((int64_t)*pc + (int32_t)((uint32_t)z << 2));
    } else {
        *pc += 4;
    }

    return -1;
}

int implementation_BNE(uint32_t op, instruction_info i, uint32_t *pc) {
    int32_t x = (int32_t)get_register(get_key('S', op, i));
    int32_t y = (int32_t)get_register(get_key('T', op, i));
    int32_t z = (int32_t)get_key('I', op, i);
    z = (int32_t)N_bit_2_comp('I', (uint32_t)z, i);

    if (x != y) {
        *pc = (uint32_t)((int64_t)*pc + (int32_t)((uint32_t)z << 2));
    } else {
        *pc += 4;
    }

    return -1;
}

int implementation_BLEZ(uint32_t op, instruction_info i, uint32_t *pc) {
    int32_t x = (int32_t)get_register(get_key('S', op, i));
    int32_t z = (int32_t)get_key('I', op, i);
    z = (int32_t)N_bit_2_comp('I', (uint32_t)z, i);

    if (x <= 0) {
        *pc = (uint32_t)((int64_t)*pc + (int32_t)((uint32_t)z << 2));
    } else {
        *pc += 4;
    }

    return -1;
}

int implementation_BGTZ(uint32_t op, instruction_info i, uint32_t *pc) {
    int32_t x = (int32_t)get_register(get_key('S', op, i));
    int32_t z = (int32_t)get_key('I', op, i);
    z = (int32_t)N_bit_2_comp('I', (uint32_t)z, i);

    if (x > 0) {
        *pc = (uint32_t)((int64_t)*pc + (int32_t)((uint32_t)z << 2));
    } else {
        *pc += 4;
    }

    return -1;
}

int implementation_BLTZ(uint32_t op, instruction_info i, uint32_t *pc) {
    int32_t x = (int32_t)get_register(get_key('S', op, i));
    int32_t z = (int32_t)get_key('I', op, i);
    z = (int32_t)N_bit_2_comp('I', (uint32_t)z, i);

    if (x < 0) {
        *pc = (uint32_t)((int64_t)*pc + (int32_t)((uint32_t)z << 2));
    } else {
        *pc += 4;
    }

    return -1;
}

int implementation_BGEZ(uint32_t op, instruction_info i, uint32_t *pc) {
    int32_t x = (int32_t)get_register(get_key('S', op, i));
    int32_t z = (int32_t)get_key('I', op, i);
    z = (int32_t)N_bit_2_comp('I', (uint32_t)z, i);

    if (x >= 0) {
        *pc = (uint32_t)((int64_t)*pc + (int32_t)((uint32_t)z << 2));
    } else {
        *pc += 4;
    }

    return -1;
}

int implementation_J(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_key('X', op, i);

    *pc = ((*pc & 0xF0000000) | (x << 2));

    return -1;
}

int implementation_JAL(uint32_t op, instruction_info i, uint32_t *pc) {
    uint32_t x = get_key('X', op, i);

    set_register(ra, (*pc) + 4);
    *pc = ((*pc & 0xF0000000) | (x << 2));

    return -1;
}

int implementation_JR(uint32_t op, instruction_info i, uint32_t *pc) {
    *pc = get_register(get_key('S', op, i));

    return -1;
}

int implementation_SYSCALL(uint32_t op, instruction_info i, uint32_t *pc) {
    (void)op;
    (void)i;
    if (get_register(v0) <= 0 || get_register(v0) >= N_SYSCALLS) {
        fprintf(stderr,
                "Syscall \'%d\' is out of range.\nTerminating program.\n",
                get_register(v0));
        return -2;
    }
    syscall_fnptr call = syscall_map[get_register(v0)];
    if (!call) {
        fprintf(stderr,
                "Syscall \'%d\' is unimplemented.\nTerminating program.\n",
                get_register(v0));
        return -2;
    }
    *pc += 4;
    return call();
}
