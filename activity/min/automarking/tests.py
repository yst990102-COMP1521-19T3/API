#!/usr/bin/python3
import re
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f min.s
files=min.s

""")

tests = [
    '15 5',
    '5 5',
    '63512 15589',
    '196 32334',
    '19228 21673',
    '961 46514',
    '61168 1837',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

