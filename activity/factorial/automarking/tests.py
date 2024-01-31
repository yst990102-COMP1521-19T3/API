#!/usr/bin/python3
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f factorial.s
files=factorial.s

""")
tests = [1, 2, 3, 6, 8, 9, 11]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} stdin="{f}\\n"')

