#include <stdlib.h>

#ifndef ASS1_SYSCALLS_H
#define ASS1_SYSCALLS_H

typedef int (*syscall_fnptr)(void);

typedef enum systemcalls {
    print_integer = 1,
    print_float,
    print_double,
    print_string,

    read_integer,
    read_float,
    read_double,
    read_string,

    sbrk,

    exit1,

    print_character,
    read_character,

    open_file,
    read_file,
    write_file,
    close_file,

    exit2,

    N_SYSCALLS,
} systemcall;

int implementation_print_integer(void);
int implementation_read_integer(void);

int implementation_print_string(void);
int implementation_read_string(void);

int implementation_print_character(void);
int implementation_read_character(void);
int implementation_exit1(void);
int implementation_exit2(void);

extern const syscall_fnptr syscall_map[];

#endif //ASS1_SYSCALLS_H
