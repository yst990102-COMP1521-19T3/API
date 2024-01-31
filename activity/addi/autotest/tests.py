#!/usr/bin/python3
import re
print("""
max_cpu=30
compiler_args=-Dmain=_main autotest_addi.c addi.c -o addi
files=addi.c

""")

tests = [
    '29 28 2345',
    '2 4 -2',
    '31 31 -1',
    '0 0 0',
    '23 25 -32760',
    '3 5 32765',
]
for (test_number, arguments) in enumerate(tests):
    print(f'{test_number} command=./addi {arguments} description="{arguments}"')


