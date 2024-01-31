#!/usr/bin/python3
import re
print("""
max_cpu=30
command=1521 spim -f positive_negative.s
files=positive_negative.s

""")

tests = [
    '1 -2 3 -4 5 -6 7 -8 9 -10',
    '1 2 3 4 5 6 7 8 9 10',
    '-1 -2 -3 -4 -5 -6 -7 -8 -9 -10',
    '1 -1 2 -2 -7 4 6 5 0 10',
    '-2 -10 -4 10 -5 -9 -1 3 2 1',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

