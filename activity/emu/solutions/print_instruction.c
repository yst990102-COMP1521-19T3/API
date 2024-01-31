#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "emu.h"

#include "instructions.h"

void print_instruction(uint32_t instruction) {
    char *tmp = op_to_instruction(instruction);
    printf("%s", tmp);
    free(tmp);
}
