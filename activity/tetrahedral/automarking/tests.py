#!/usr/bin/python3
print("""
max_cpu=60
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f tetrahedral.s
files=tetrahedral.s

""")
tests = [6, 7, 9, 11, 12, 24, 66]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} stdin="{f}\\n"')

