#!/usr/bin/python3
print("""
max_cpu=30
command=1521 spim -f three_five.s
files=three_five.s

""")
tests = [6, 10, 11, 12, 42, 75]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} stdin="{f}\\n"')

