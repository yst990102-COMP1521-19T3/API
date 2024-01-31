#!/usr/bin/python3
import re
print("""
max_cpu=30
command=1521 spim -f not_negative.s
files=not_negative.s

""")

tests = [
    '-5 -1 24',
    '-1 -2 -3 -3 -4 -5 0',
    '100',
    '-100 1',
    '-1 -1 1',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

