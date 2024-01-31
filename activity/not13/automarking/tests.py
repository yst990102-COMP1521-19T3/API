#!/usr/bin/python3
import re
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f not13.s
files=not13.s

""")

tests = [
    '10 16',
    '4 12',
    '8 43',
    '3 21',
    '41 49',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

