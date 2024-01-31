#!/usr/bin/python3
import re
print("""
max_cpu=30
command=1521 spim -f print_bigger.s
files=print_bigger.s

""")

tests = [
    '1 2 3 4 5 6 7 8 9 10',
    '1 2 3 4 5 6 7 8 9 5',
    '1 2 3 4 5 6 7 8 9 1',
    '1 2 3 4 5 6 7 8 9 0',
    '5 5 5 5 5 4 5 5 5 5',
    '5 5 5 5 5 4 5 5 5 4',
    '25664 11593 12172 17 30727 8527 23102 26011 28344 5565',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

