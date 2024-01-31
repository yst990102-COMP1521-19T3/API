#!/usr/bin/python3
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f count.s
files=count.s

""")
tests = [6, 10, 11, 12, 48, 51, 64, 66, 85, 99, 1001, 1002, 1003]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} stdin="{f}\\n"')

