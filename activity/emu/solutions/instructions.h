#include <stdbool.h>
#include <stdint.h>

#ifndef ASS1__INSTRUCTIONS_H
#define ASS1__INSTRUCTIONS_H

typedef struct instruction_info instruction_info;

/// `impl_fnptr' is a function that takes an opcode, an instruction, and
/// a reference to the program counter, and returns an error code:
///
///  - >= 0 for syscall exit;
///  - -1 otherwise
///  - -2 outside text_segment
///  - -3 ... other errors
///
/// This is slightly different to how execute_next_instruction() returns;
/// see ram.c.
typedef int (*impl_fnptr)(uint32_t, instruction_info, uint32_t *);

struct instruction_info {
    char *name;

    bool is_table;
    const void *linked_table;
    uint32_t linked_table_key_mask;

    char *encoding;

    char *format;
    int default_reg;

    impl_fnptr implementation;
};

extern const instruction_info instruction_map[];

int run_instruction(uint32_t, uint32_t *);
char *op_to_instruction(uint32_t);

#endif // !defined(ASS1__INSTRUCTIONS_H)
