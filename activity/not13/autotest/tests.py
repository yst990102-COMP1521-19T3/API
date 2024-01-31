#!/usr/bin/python3
import re
print("""
max_cpu=30
command=1521 spim -f not13.s
files=not13.s

""")

tests = [
    '11 15',
    '5 11',
    '9 42',
    '1 20',
    '42 48',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

