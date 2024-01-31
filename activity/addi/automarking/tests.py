#!/usr/bin/python3
import re
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
compiler_args=-Dmain=_main autotest_addi.c addi.c -o addi
files=addi.c

""")

tests = [
    '27 28 23456',
    '12 14 -12',
    '30 30 -2',
    '0 0 0',
    '22 15 -32761',
    '13 15 32761',
]
for (test_number, arguments) in enumerate(tests):
    print(f'{test_number} command=./addi {arguments} description="{arguments}"')


