#!/usr/bin/python3
print("""
max_cpu=240
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f big_factorial.s
files=big_factorial.s

""")
from functools import reduce

tests = [47, 193, 212, 1512]
for (test_number, n) in enumerate(tests):
    factorial = reduce(lambda x, y: x * y, range(1, n+1))
    expected_stdout = f'Loaded: /home/cs1521/share/spim/exceptions.s\\nEnter n: {n}! = {factorial}\\n'
    print(f'{test_number} stdin="{n}\\n" description="{n}" expected_stdout="{expected_stdout}"')

