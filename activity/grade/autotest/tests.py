#!/usr/bin/python3
print("""
max_cpu=30
command=1521 spim -f grade.s
files=grade.s

""")
tests = [49, 50, 74, 76, 85, 100]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} stdin="{f}\\n"')

