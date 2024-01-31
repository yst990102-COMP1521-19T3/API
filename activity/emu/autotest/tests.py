#! /usr/bin/env python3
import re

print("""
max_cpu=60
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
    add $20, $21, $22
    sub $20, $21, $14
    mul $24, $20, $2
    and $23, $12, $8
    or $5, $12, $10
    xor $2, $10, $22
    sllv $15, $2, $14
    srlv $6, $7, $2
    slt $17, $21, $5
    addi $6, $16, 27
    andi $14, $13, 3
    ori $18, $15, 25
    xori $14, $23, 19
    sll $5, $19, 27
    srl $8, $13, 18
    slti $7, $7, 17
    lui $11, 35
    lb $13, 22($18)
    lh $14, 20($2)
    lw $7, 7($21)
    sb $21, 33($15)
    sh $11, 20($15)
    sw $17, 13($19)
    beq $10, $17, main
    bne $17, $23, main
    blez $19, main
    bgtz $23, main
    bltz $7, main
    bgez $17, main
    j main
    jal main
    jr $2
    syscall
"""

part1_instruction_tests = [t.strip() for t in part1_instructions.split('\n') if t.strip()]

test_number = 0
for instruction in part1_instruction_tests:
    print(f'part1_{test_number:02d} command="./emu -p \'{instruction}\'" description="{instruction}"')
    test_number += 1

asm_files = "42.s  add.s  print10.s sum_100_squares.s add_memory.s read10.s reverse10.s".split()

for pathname in asm_files:
    print(f'part1_{test_number:02d} command="./emu -P \'{pathname}\'" description="{pathname}"')
    test_number += 1


extra_part1_instructions = """
    addi $6, $16, -27
    lw $7, -4($21)
    sb $21, -1($15)
    sh $11, -32000($15)
    sw $17, -12($19)
    0x1151FFF0
    0x155100A0
"""

extra_part1_instruction_tests = [t.strip() for t in part1_instructions.split('\n') if t.strip()]

for instruction in part1_instruction_tests:
    print(f'part1_{test_number:02d} command="./emu -p \'{instruction}\'" description="{instruction}"')
    test_number += 1

part2_instructions = """
    add $7, $15, $12
    sub $20, $16, $11
    mul $24, $13, $14
    and $23, $28, $29
    or $5, $31, $10
    xor $2, $29, $28
    sllv $15, $14, $14
    srlv $6, $15, $13
    slt $17, $13, $14
    addi $6, $15, 22
    andi $14, $13, 3
    ori $18, $15, 25
    xori $14, $15, 19
    sll $5, $29, 27
    srl $8, $31, 18
    slti $7, $7, 17
    lui $15, 35
"""

test_number = 0
part2_instruction_tests = [t.strip() for t in part2_instructions.split('\n') if t.strip()]

for instruction in part2_instruction_tests:
    print(f'part2_{test_number:02d} command="./emu -e \'{instruction}\'" description="{instruction}"')
    test_number += 1

ten_numbers="1\\n2\\n3\\n4\\n5\\n6\\n7\\n8\\n9\\n10\\n"
for pathname in asm_files :
    print(f'part2_{test_number:02d} command="./emu -E \'{pathname}\'" description="{pathname}"', end='')
    if pathname in ['read10.s', 'reverse10.s']:
        print(f' stdin="{ten_numbers}"')
    else:
        print()
    test_number += 1


extra_part2_instructions = """
    slt $17, $13, $29
    lui $2, 4097; lw $17, 0($2); .data; .word 0xfffefdfc
    lui $2, 4097; lh $18, 2($2); .data; .word 0xfffefdfc
    lui $2, 4097; lb $19, 1($2); .data; .word 0xfffefdfc
    lui $2, 4096; sw $29, 0($2); lw $7, 0($2)
    lui $2, 4096; sw $29, 0($2); lh $8, 2($2)
    lui $2, 4096; sw $29, 0($2); lb $9, 1($2)
    lui $2, 4097; sb $29, 1($2); lw $10, 0($2); .data; .word 0xfffefdfc
    lui $2, 4097; sh $29, 2($2); lw $11, 0($2); .data; .word 0xfffefdfc
"""

extra_part2_instruction_tests = [t.strip() for t in extra_part2_instructions.split('\n') if t.strip()]

for instructions_line in extra_part2_instruction_tests:
    instructions = ' '.join([f"'{i}'" for i in re.split(r'\s*;\s*', instructions_line.strip())])
    print(f'part2_{test_number:02d} command="./emu -e {instructions}" description="{instructions}"')
    test_number += 1
