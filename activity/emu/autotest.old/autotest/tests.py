#! /usr/bin/env python3
from subprocess import run, PIPE
from shutil import rmtree, move
from os import mkdir, listdir
from os.path import join, realpath, dirname, isfile

rmtree(join(dirname(realpath(__file__)), "MIPS_assembled/"), ignore_errors=True)
mkdir(join(dirname(realpath(__file__)), "MIPS_assembled/"))

for filename in listdir(join(dirname(realpath(__file__)), "MIPS_src")):
    if not isfile(join(dirname(realpath(__file__)), "MIPS_src", filename)): continue
    run(['1521', 'spim', '-assemble', '-f', join(dirname(realpath(__file__)), "MIPS_src", filename)], stdout=PIPE)
    move(join(dirname(realpath(__file__)), "MIPS_src", filename+'.out'),
         join(dirname(realpath(__file__)), "MIPS_assembled", filename+'.out'))

tests = [
    ('42.s',      '-p', '/dev/null',       '42.s.print'),

    ('42.s',      '-r', '/dev/null',       '42.s.stdout'),
]

print("""
max_cpu=60
compiler_args=emu.c ram.c registers.c execute_instruction.c print_instruction.c -o emu
files=execute_instruction.c print_instruction.c

""")

for (test_number, filename) in enumerate(tests):
    with open(join(dirname(realpath(__file__)), "MIPS_exp", filename[2]), 'r') as in_file, \
            open(join(dirname(realpath(__file__)), "MIPS_exp", filename[3]), 'r') as out_file:
        print('{} command=./emu {} {} stdin={} expected_stdout={} '.format(
            test_number, filename[1], join(dirname(realpath(__file__)), "MIPS_assembled", filename[0]+".out"),
            "\\n".join([l.replace("\n", "") for l in in_file.readlines()]),
            "\\n".join([l.replace("\n", "") for l in out_file.readlines()])))
