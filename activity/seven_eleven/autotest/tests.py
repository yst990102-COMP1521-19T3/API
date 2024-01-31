#!/usr/bin/python3
print("""
max_cpu=30
command=1521 spim -f seven_eleven.s
files=seven_eleven.s

""")
tests = [6, 10, 11, 12, 42, 75]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} stdin="{f}\\n"')

