#include <stdint.h>

#include "emu.h"

#include "instructions.h"

int execute_instruction(uint32_t instruction, uint32_t *program_counter) {
    return run_instruction(instruction, program_counter);
}
