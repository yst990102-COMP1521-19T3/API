#!/usr/bin/python3
import re
print("""
max_cpu=30
command=1521 spim -f different10.s
files=different10.s

""")

tests = [
    '1 2 3 4 5 6 7 8 9 10 2 3 4',
    '1 2 1 3 2 4 5 6 7 9 10 7 6 5 6 8 2 3 3',
    '25664 11593 12172 17 30727 8527 23102 26011 28344 5565 67 1 2 3',
    '1 1 1 1 1 1 1 1 1 1 25664 11593 12172 17 30727 8527 23102 26011 28344 5565 67 1 2 3'
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

