#!/usr/bin/python3
import re
print("""
max_cpu=30
command=1521 spim -f lookup.s
files=lookup.s

""")

tests = [
    '0 0',
    '41 23',
    '11 13',
    '9 7',
    '5 5',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

