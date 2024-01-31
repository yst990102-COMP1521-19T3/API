#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "instructions.h"
#include "registers.h"

static bool validate_instruction(uint32_t opcode,
                                 instruction_info instruction) {
    // Is this really necessary if we have to pass the SPIM assembler first?
    // I guess you could hand craft a dirty *.s.out
    (void)opcode;
    (void)instruction;
    return 1;
}

static instruction_info get_instruction_info(uint32_t opcode) {
    const instruction_info *base =
        &instruction_map[(opcode & 0xFC000000) >> 26];
    while (base->is_table) {
        if (!base->linked_table) {
            fprintf(
                stderr,
                "Instruction Table \"%s\" is unimplemented.\nTerminating program.\n",
                base->name);
            exit(2);
        }
        uint32_t mask = base->linked_table_key_mask;
        uint32_t key = (opcode & mask);
        for (; !(mask & 1); mask >>= 1, key >>= 1) {
            ;
        }
        base = &(((const instruction_info *)base->linked_table)[key]);
    }
    if (!validate_instruction(opcode, *base)) {
        fprintf(
            stderr,
            "Instruction bits \"0x%X\" dont match format of instruction \"%s\".\nTerminating program.\n",
            opcode, base->name);
        exit(2);
    }
    return *base;
}

int run_instruction(uint32_t opcode, uint32_t *program_counter) {
    instruction_info instruction = get_instruction_info(opcode);
    if (!instruction.implementation) {
        fprintf(stderr,
                "Instruction \'%s\' is unimplemented.\nTerminating program.\n",
                instruction.name);
        return -2;
    }
    int ret =
        (*(instruction.implementation))(opcode, instruction, program_counter);

    if (ret >= 0) return 1; // return from syscall 10
    else if (ret == -1) return 0; // return from normal instruction
    else return ret;
}

char *op_to_instruction(uint32_t opcode) {
    instruction_info instruction = get_instruction_info(opcode);
    char *ret = strdup(instruction.name);
    bool is_first = true;
    for (char *c = instruction.format; *c; c++) {
        uint32_t key, key_bits;
        {
            uint32_t mask = ~((~0u) >> 1);
            key = 0;
            char *mask_start = strchr(instruction.encoding, toupper(*c));
            char *mask_end = strrchr(instruction.encoding, toupper(*c));
            char *encoding_end = strchr(instruction.encoding, '\0');
            for (char *_ = instruction.encoding; _ != mask_start;
                 mask >>= 1, _++) {
                ;
            }
            for (char *_ = mask_start; _ <= mask_end; mask >>= 1, _++) {
                key |= opcode & mask;
            }
            key >>= (encoding_end - mask_end) - 1;
            key_bits = (uint32_t)(mask_end - mask_start) + 1;
        }
        switch (*c) {
        case 'S':
        case 's':
        case 'T':
        case 't':
        case 'D':
        case 'd':
        case 'A':
        case 'a': {
            if (islower(*c) && (int)key == instruction.default_reg) {
                continue;
            }
            if (is_first) {
                ret = realloc(ret, strlen(ret) + strlen(" ") + 1);
                strcat(ret, " ");
            } else {
                ret = realloc(ret, strlen(ret) + strlen(", ") + 1);
                strcat(ret, ", ");
            }
            {
                // const char *_ = register_name_map[key];
                char _[16];
                snprintf(_, sizeof _, "$%d", key);
                ret = realloc(ret, strlen(ret) + strlen(_) + 1);
                strcat(ret, _);
            }
            break;
        }
        case 'I':
        case 'U': {
            if (is_first) {
                ret = realloc(ret, strlen(ret) + strlen(" ") + 1);
                strcat(ret, " ");
            } else {
                ret = realloc(ret, strlen(ret) + strlen(", ") + 1);
                strcat(ret, ", ");
            }
            {
                if (*c == 'I') {
                    if (key & 1ul << (key_bits - 1)) {
                        uint32_t mask = ~((~0u) >> 1);
                        while (!(key & mask)) {
                            key |= mask;
                            mask >>= 1;
                        }
                    }
                }
            }
            {
                char *_ = malloc((size_t)snprintf(NULL, 0, "%d", key) + 1);
                sprintf(_, "%d", key);
                ret = realloc(ret, strlen(ret) + strlen(_) + 1);
                strcat(ret, _);
                free(_);
            }
            break;
        }
        case 'X': {
            if (is_first) {
                ret = realloc(ret, strlen(ret) + strlen(" ") + 1);
                strcat(ret, " ");
            } else {
                ret = realloc(ret, strlen(ret) + strlen(", ") + 1);
                strcat(ret, ", ");
            }
            {
                char *_ = malloc((size_t)snprintf(NULL, 0, "0x%X", key) + 1);
                sprintf(_, "0x%X", key);
                ret = realloc(ret, strlen(ret) + strlen(_) + 1);
                strcat(ret, _);
                free(_);
            }
            break;
        }
        case 'O': {
            if (is_first) {
                ret = realloc(ret, strlen(ret) + strlen(" ") + 1);
                strcat(ret, " ");
            } else {
                ret = realloc(ret, strlen(ret) + strlen(", ") + 1);
                strcat(ret, ", ");
            }
            {
                if (key & 1ul << (key_bits - 1)) {
                    uint32_t mask = ~((~0u) >> 1);
                    while (!(key & mask)) {
                        key |= mask;
                        mask >>= 1;
                    }
                }
            }
            {
                char *_ = malloc((size_t)snprintf(NULL, 0, "%d", key) + 1);
                sprintf(_, "%d", key);
                ret = realloc(ret, strlen(ret) + strlen(_) + 1);
                strcat(ret, _);
                free(_);
            }
            {
                ret = realloc(ret, strlen(ret) + strlen("(") + 1);
                strcat(ret, "(");
            }
            {
                uint32_t mask = ~((~0u) >> 1);
                key = 0;
                char *mask_start = strchr(instruction.encoding, 'B');
                char *mask_end = strrchr(instruction.encoding, 'B');
                char *encoding_end = strchr(instruction.encoding, '\0');
                for (char *_ = instruction.encoding; _ != mask_start;
                     mask >>= 1, _++) {
                    ;
                }
                for (char *_ = mask_start; _ <= mask_end; mask >>= 1, _++) {
                    key |= opcode & mask;
                }
                key >>= (encoding_end - mask_end) - 1;
                key_bits = (uint32_t)(mask_end - mask_start) + 1;
            }
            {
                // const char *_ = register_name_map[key];
                char _[16];
                snprintf(_, sizeof _, "$%d", key);
                ret = realloc(ret, strlen(ret) + strlen(_) + 1);
                strcat(ret, _);
            }
            {
                ret = realloc(ret, strlen(ret) + strlen(")") + 1);
                strcat(ret, ")");
            }
            break;
        }
        case 'B':
            break;
        default: {
            fprintf(
                stderr,
                "Unknown encoding \"%c\" for instruction \"%s\".\nTerminating program.\n",
                *c, instruction.name);
            exit(3);
        }
        }
        is_first = false;
    }
    return strcat(realloc(ret, strlen(ret) + 3),
                  instruction.implementation ? "" : " !");
}
