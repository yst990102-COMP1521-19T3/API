#!/usr/bin/python3
import re
print("""
max_cpu=30
command=1521 spim -f min.s
files=min.s

""")

tests = [
    '12 15',
    '17 11',
    '9 42',
    '100 2',
    '42 42',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

