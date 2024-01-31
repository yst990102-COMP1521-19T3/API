#!/usr/bin/python3
import re
print("""
max_cpu=60
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f unordered.s
files=unordered.s

""")

tests = [
    '0 2 3 4 5 6 7 8 9 12',
    '1 2 3 4 7 6 7 8 9 10',
    '5 5 5 5 5 5 5 5 5 5',
    '5 5 5 5 5 5 5 5 3 5',
    '5 8 5 5 5 5 5 5 5 5',
    '1 2 4 8 16 32 64 128 129 512 1024',
    '1 2 4 8 16 32 64 128 126 512 1024',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

