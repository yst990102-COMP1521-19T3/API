#!/usr/bin/python3
print("""
max_cpu=30
command=1521 spim -f tetrahedral.s
files=tetrahedral.s

""")
tests = [1, 2, 3, 42]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} stdin="{f}\\n"')

