#!/usr/bin/python3
import re
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f lookup.s
files=lookup.s

""")

tests = [
    '0 0',
    '41 23',
    '21 23',
    '19 17',
    '3 3',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

