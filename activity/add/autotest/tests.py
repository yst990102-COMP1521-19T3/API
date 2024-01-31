#!/usr/bin/python3
import re
print("""
max_cpu=30
compiler_args=-Dmain=_main autotest_add.c add.c -o add
files=add.c

""")

tests = [
    '29 28 11',
    '2 4 12',
    '31 31 11',
    '0 0 0',
    '31 31 31',
    '3 5 27',
]
for (test_number, arguments) in enumerate(tests):
    print(f'{test_number} command=./add {arguments} description="{arguments}"')


