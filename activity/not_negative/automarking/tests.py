#!/usr/bin/python3
import re
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f not_negative.s
files=not_negative.s

""")

tests = [
   '-5 -6 224',
    '-11 -2 -13 -3 -14 -115 0',
    '10000',
    '-10000 1',
    '-10 -10 10',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

