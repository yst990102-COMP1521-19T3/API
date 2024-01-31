#!/usr/bin/python3
import re
print("""
max_cpu=30
command=1521 spim -f unordered.s
files=unordered.s

""")

tests = [
    '1 2 3 4 5 6 7 8 9 10',
    '1 2 3 4 15 6 7 8 9 10',
    '5 5 5 5 5 5 5 5 5 5',
    '5 5 5 5 5 5 5 5 5 4',
    '6 5 5 5 5 5 5 5 5 5',
    '1 2 4 8 16 32 64 128 256 512 1024',
    '1 2 4 8 16 15 64 128 256 512 1024',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

