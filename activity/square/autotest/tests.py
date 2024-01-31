#!/usr/bin/python3
import re
print("""
max_cpu=30
command=1521 spim -f square.s
files=square.s

""")

tests = [
    '1',
    '2',
    '5',
    '11',
    '43',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

