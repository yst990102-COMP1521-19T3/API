#!/usr/bin/python3
import re
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
compiler_args=-Dmain=_main autotest_add.c add.c -o add
files=add.c

""")

tests = [
    '27 28 23',
    '12 14 12',
    '30 30 2',
    '0 0 0',
    '22 15 16',
    '13 15 1',
]
for (test_number, arguments) in enumerate(tests):
    print(f'{test_number} command=./add {arguments} description="{arguments}"')


