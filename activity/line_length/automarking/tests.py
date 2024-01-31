#!/usr/bin/python3
import re
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f line_length.s
files=line_length.s

""")

tests = [
    'hellohello',
    'I MIPS you a lot',
    'Good bye now',
    '244',
    '--*-----',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

