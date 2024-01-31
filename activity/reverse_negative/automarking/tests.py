#!/usr/bin/python3
import re
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f reverse_negative.s
files=reverse_negative.s

""")

tests = [
    '15 4 1 42 -3',
    '1 2 3 4 5 6 7 8 9 10 -1',
    '25664 11593 12172 17 30727 8527 23102 26011 28344 5565 -67',
    '1 2 3 4 5 6 7 8 9 8 7 6 -1',
    '15 4 1 42 15 4 1 42 15 4 1 42 -3',
    '1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10 -1',
    '25664 11593 12172 17 30727 8527 23102 26011 28344 5565 25664 11593 12172 17 30727 8527 23102 26011 28344 5565 -67',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

