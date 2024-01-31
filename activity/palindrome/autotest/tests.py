#!/usr/bin/python3
import re
print("""
max_cpu=30
command=1521 spim -f palindrome.s
files=palindrome.s

""")

tests = [
    'kayak',
    'canoe',
    'repaper',
    'repacker',
    '0123210',
    '0133210',
    '0123310',
    '01233210',
    '01234210',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

