#include <stdint.h>
#include <stdio.h>

#include "ram.h"
#include "registers.h"
#include "syscalls.h"

const syscall_fnptr syscall_map[] = {
    [print_integer] = implementation_print_integer,
    [print_float] = NULL,
    [print_double] = NULL,
    [print_string] = implementation_print_string,
    [read_integer] = implementation_read_integer,
    [read_float] = NULL,
    [read_double] = NULL,
    [read_string] = implementation_read_string,
    [sbrk] = NULL,
    [exit1] = implementation_exit1,
    [print_character] = implementation_print_character,
    [read_character] = implementation_read_character,
    [open_file] = NULL,
    [read_file] = NULL,
    [write_file] = NULL,
    [close_file] = NULL,
    [exit2] = implementation_exit2,
};

int implementation_print_integer(void) {
    printf("%d", (int32_t)get_register(a0));
    return -1;
}

int implementation_read_integer(void) {
    int in = 0;
    scanf("%d", &in);
    set_register(v0, in);
    return -1;
}

int implementation_print_string(void) {
    uint32_t base = get_register(a0);
    char byte = '\0';
    while ((byte = (char)get_byte(base))) {
        putchar(byte);
        base++;
    }
    return -1;
}

int implementation_read_string(void) {
    uint32_t base = get_register(a0);
    uint32_t size = get_register(a1);
    if (size == 0) {
        return -1;
    }
    char *line = NULL;
    size_t n = 0;
    ssize_t length = getline(&line, &n, stdin);
    ssize_t i = 0;
    for (; i < length && i < size - 1; i++) {
        set_byte(base + (size_t)i, (unsigned char)line[i]);
    }
    for (; i < size; i++) {
        set_byte(base + (size_t)i, '\0');
    }
    free(line);
    return -1;
}

int implementation_print_character(void) {
    putchar(get_register(a0));
    return -1;
}

int implementation_read_character(void) {
    char in = 0;
    scanf("%c", &in);
    set_register(v0, (unsigned char)in);
    return -1;
}

int implementation_exit1(void) {
    return 0;
}

int implementation_exit2(void) {
    return (int)get_register(a0);
}
