#! /usr/bin/env python3
import re,sys

print("""
max_cpu=15
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
pre_compile_command="mv supplied_files/* . 2>/dev/null"
pre_compile_command_shell=1

# have to run sanitizers separately because we are using unistd.h
compilers="dcc -fsanitize=address:dcc -fsanitize=valgrind"

# don't ask
compiler_args='`ls *.c`' -o emu
files=execute_instruction.c print_instruction.c
shell=1
""")

part1_instructions = """
    add $4, $24, $20
    add $26, $12, $10

    sub $25, $6, $10
    sub $9, $25, $25

    mul $9, $29, $17
    mul $11, $6, $25

    and $18, $20, $7
    and $15, $20, $4

    or $22, $8, $15
    or $4, $9, $4

    xor $23, $11, $27
    xor $27, $31, $14

    sllv $19, $3, $27
    sllv $22, $18, $12

    srlv $11, $4, $26
    srlv $2, $15, $14

    slt $18, $21, $26
    slt $11, $29, $23

    addi $17, $26, 21
    addi $7, $30, -18

    andi $3, $28, 25
    andi $27, $10, 12

    ori $7, $17, 24
    ori $18, $5, 17

    xori $30, $16, 21
    xori $27, $21, 22

    sll $12, $14, 26
    sll $11, $14, 16

    srl $12, $26, 31
    srl $30, $20, 8

    slti $25, $5, 31
    slti $2, $13, -20

    lui $10, 17
    lui $2, 24

    lb $18, 13($21)
    lb $11, -8($9)

    lh $7, 6($18)
    lh $21, -29($29)

    lw $18, -11($21)
    lw $13, 2($11)

    lw $20, 19($16)
    lw $12, -2($6)

    sb $21, 15($4)
    sb $10, -11($29)

    sh $28, 26($12)
    sh $14, -21($23)

    sw $26, 2($17)
    sw $31, -4($9)

    0x1151FFF2  # beq $10, $17, -14
    0x1151000A  # beq $10, $17, 10

    0x15510080  # bne $10, $17, 128
    0x1551EEEA  # bne $10, $17, -4374

    0x1840000A  # blez $2, 10
    0x1840DDDA  # blez $2, -8742

    0x1DA000BA # bgtz $13, 186
    0x1DAAAAAA # bgtz $13, -21846

    0x06E0000F # bltz $23, 15
    0x06E0FFF0 # bltz $23, -16

    0x07E10200 # bgez $31, 512
    0x07E1FCFF # bgez $31, -769

    0x0810000A # j 0x10000A
    0x0ABADEAD # j 0x2BADEAD

    0x0C1000BA # jal  0x1000BA
    0x0EBADEED # jal 0x2BADEED

    jr $5
    jr $17

    syscall

"""

part1_instruction_tests = [re.sub(r'#.*', '', t).strip() for t in part1_instructions.split('\n') if t.strip()]

test_number = 0
for instruction in part1_instruction_tests:
    print(f'part1_{test_number:02d} command="./emu -p \'{instruction}\'" description="{instruction}"')
    test_number += 1

asm_files = "42.s  add.s  print10.s sum_100_squares.s add_memory.s read10.s reverse10.s bad_pun.s exit.s read_char.s square.s print_array.s max.s danish_flag.s and-simpler.s and.s triangle.s loop.s factorial.s bubblesort.s sieve.s first_character.s line_length.s lookup.s".split()

for pathname in asm_files:
    print(f'part1_{test_number:02d} command="./emu -P \'{pathname}\'" description="{pathname}"')
    test_number += 1

part2_instructions = """
    add $10, $11, $14
    add $16, $12, $12

    sub $13, $10, $13
    sub $14, $12, $13

    mul $15, $11, $13
    mul $12, $14, $14

    and $9, $15, $11
    and $9, $14, $11

    or $13, $15, $16
    or $11, $11, $10

    xor $13, $11, $11
    xor $10, $12, $9

    sllv $11, $15, $15
    sllv $14, $9, $12

    srlv $10, $14, $16
    srlv $10, $15, $13

    slt $11, $12, $14
    slt $10, $10, $11

    addi $16, $12, 24
    addi $13, $14, -11

    andi $9, $11, 31
    andi $14, $9, 29

    ori $10, $11, 3
    ori $9, $15, 25

    xori $11, $16, 3
    xori $16, $10, 22

    sll $14, $10, 9
    sll $12, $15, 24

    srl $15, $11, 14
    srl $13, $14, 12

    slti $10, $14, 21
    slti $11, $9, -16

    lui $10, 15
    lui $9, 9

    slt $12, $15, $12
    slt $13, $15, $15
    slt $12, $13, $15
    slt $2, $29, $15

    lui $2, 4097; lh $18, 2($2); .data; .word 0xaeadacab
    lui $2, 4097; lb $19, 1($2); .data; .word 0xaeadacab
    lui $2, 4097; lw $17, 0($2); .data; .word 0x01020304
    lui $2, 4097; lh $18, 2($2); .data; .word 0x01020304
    lui $2, 4097; lb $19, 1($2); .data; .word 0x01020304
    lui $2, 4097; lw $17, 0($2); .data; .word 0xaeadacab
    lui $2, 4097; lh $18, 2($2); .data; .word 0xaeadacab
    lui $2, 4097; lb $19, 1($2); .data; .word 0xaeadacab
    lui $2, 4096; sw $29, 0($2); lw $7, 0($2)
    lui $2, 4096; sw $29, 0($2); lh $8, 2($2)
    lui $2, 4096; sw $29, 0($2); lb $9, 1($2)
    lui $2, 4097; sb $29, 1($2); lw $10, 0($2); .data; .word 0xaeadacab
    lui $2, 4097; sh $29, 2($2); lw $11, 0($2); .data; .word 0xaeadacab

    beq $8, $0, label; addi $8, $8, 1; label: addi $8, $8, 1
    beq $9, $0, label; addi $8, $8, 1; label: addi $8, $8, 1

    bne $8, $0, label; addi $8, $8, 1; label: addi $8, $8, 1
    bne $9, $0, label; addi $8, $8, 1; label: addi $8, $8, 1

    blez  $9, label; addi $8, $8, 1; label: addi $8, $8, 1
    blez  $8, label; addi $8, $8, 1; label: addi $8, $8, 1
    blez $29, label; addi $8, $8, 1; label: addi $8, $8, 1

    bgtz  $9, label; addi $8, $8, 1; label: addi $8, $8, 1
    bgtz  $8, label; addi $8, $8, 1; label: addi $8, $8, 1
    bgtz $29, label; addi $8, $8, 1; label: addi $8, $8, 1

    bltz  $9, label; addi $8, $8, 1; label: addi $8, $8, 1
    bltz  $8, label; addi $8, $8, 1; label: addi $8, $8, 1
    bltz $29, label; addi $8, $8, 1; label: addi $8, $8, 1

    bgez  $9, label; addi $8, $8, 1; label: addi $8, $8, 1
    bgez  $8, label; addi $8, $8, 1; label: addi $8, $8, 1
    bgez $29, label; addi $8, $8, 1; label: addi $8, $8, 1

    j label; addi $8, $8, 1; label: addi $8, $8, 1

    jal label; addi $8, $8, 1; label: addi $8, $8, 1

    la $2, label; jr $2; addi $8, $8, 1; label: addi $8, $8, 1
    jr $31
"""

print("max_cpu=10\n")

test_number = 0
part2_instruction_tests = [t.strip() for t in part2_instructions.split('\n') if t.strip()]

for instructions_line in part2_instruction_tests:
    instructions = ' '.join([f"'{i}'" for i in re.split(r'\s*;\s*', instructions_line.strip())])
    print(f'part2_{test_number:02d} command="./emu -e {instructions}" description="{instructions}"')
    test_number += 1

print("max_cpu=60\n")

ten_numbers="1\\n2\\n3\\n4\\n5\\n6\\n7\\n8\\n9\\n10\\n"

stdin = {
    'read10.s' : ten_numbers,
    'reverse10.s' : ten_numbers,
    'square.s' : '42\\n',
    'factorial.s' : '6\\n',
    'and.s' : '500\\n',
    'and-simpler.s' : '500\\n',
    'bubblesort.s' : "7\\n8\\n9\\n1\\n2\\n5\\n6\\n10\\n3\\n4\\n",
    'first_character' : 'hello\\n',
    'line_length.s' : 'hello\\n',
    'read_char.s' : 'hello\\n',
    'lookup.s' : '4\\n5\\n',
}

for pathname in asm_files :
    print(f'part2_{test_number:02d} command="./emu -E \'{pathname}\'" description="{pathname}"', end='')
    if pathname in stdin:
        print(f' stdin="{stdin[pathname]}"')
    else:
        print()
    test_number += 1
